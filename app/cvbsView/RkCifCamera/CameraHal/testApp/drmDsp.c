#include <stdio.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <drm_fourcc.h>
#include <string.h>

#include "./drmDsp/dev.h"
#include "./drmDsp/bo.h"
#include "./drmDsp/modeset.h"
#include "xf86drm.h"
#include "xf86drmMode.h"
#include "drmDsp.h"

struct drmDsp {
  struct fb_var_screeninfo vinfo;
  unsigned long screensize;
  char* fbp;
  struct sp_dev* dev;
  struct sp_plane** plane;
  struct sp_crtc* test_crtc;
  struct sp_plane* test_plane;
  int num_test_planes;
  struct sp_bo* bo[2];
  struct sp_bo* nextbo;
} gDrmDsp;

int initDrmDsp() {
  int ret = 0, i = 0;
  struct drmDsp* pDrmDsp = &gDrmDsp;

  memset(pDrmDsp, 0, sizeof(struct drmDsp));

  pDrmDsp->dev = create_sp_dev();
  if (!pDrmDsp->dev) {
    printf("Failed to create sp_dev\n");
    return -1;
  }

  ret = initialize_screens(pDrmDsp->dev);
  if (ret) {
    printf("Failed to initialize screens\n");
    return ret;
  }
  pDrmDsp->plane = calloc(pDrmDsp->dev->num_planes, sizeof(struct sp_plane*));
  if (!pDrmDsp->plane) {
    printf("Failed to allocate plane array\n");
    return -1;
  }

  pDrmDsp->test_crtc = &pDrmDsp->dev->crtcs[0];
  pDrmDsp->num_test_planes = pDrmDsp->test_crtc->num_planes;
  for (i = 0; i < pDrmDsp->test_crtc->num_planes; i++) {
    pDrmDsp->plane[i] = get_sp_plane(pDrmDsp->dev, pDrmDsp->test_crtc);
    if (is_supported_format(pDrmDsp->plane[i], DRM_FORMAT_NV12))
      pDrmDsp->test_plane = pDrmDsp->plane[i];
  }
  if (!pDrmDsp->test_plane) {
    printf("Failed to find plane that support NV12\n");
    return -1;
  }
  return 0;
}
struct sp_bo* bo_list_search(struct drmDsp *pDrmDsp, int dmaFd)
{
  struct sp_bo *bo = pDrmDsp->nextbo;

  while (bo) {
    if (bo->fd == dmaFd)
      return bo;
    bo = bo->next;
  }
  return NULL;
}

void bo_list_add_head(struct drmDsp *pDrmDsp, struct sp_bo *bo)
{
  struct sp_bo *tmp_bo;

  tmp_bo = pDrmDsp->nextbo;
  pDrmDsp->nextbo = bo;
  bo->next = tmp_bo;
}

void bo_list_free(struct drmDsp *pDrmDsp)
{
  struct sp_bo *bo = pDrmDsp->nextbo;
  struct sp_bo *tmp;

  while (bo) {
    int ret;

    if (!bo)
      return;

    if (bo->map_addr)
      munmap(bo->map_addr, bo->size);

    if (bo->fb_id) {
      ret = drmModeRmFB(bo->dev->fd, bo->fb_id);
      if (ret)
        printf("Failed to rmfb ret=%d!\n", ret);
    }
    tmp = bo;
    bo = bo->next;
    free(tmp);
  }
}

void deInitDrmDsp() {
  struct drmDsp* pDrmDsp = &gDrmDsp;
  printf("deInitDrmDsp\n");
  if (pDrmDsp->bo[0])
    free_sp_bo(pDrmDsp->bo[0]);
  if (pDrmDsp->bo[1])
    free_sp_bo(pDrmDsp->bo[1]);
  printf("before free bolist\n");
  fflush(stdout);
  bo_list_free(pDrmDsp);
  printf("after free bolist\n");
  fflush(stdout);
  destroy_sp_dev(pDrmDsp->dev);
  memset(pDrmDsp, 0, sizeof(struct drmDsp));
}

int drmDspFrame(int width, int height, int dmaFd, int fmt) {
  int ret;
  struct drm_mode_create_dumb cd;
  struct sp_bo* bo;
  struct drmDsp* pDrmDsp = &gDrmDsp;
  int wAlign16 = ((width + 15) & (~15));
  int hAlign16 = ((height + 15) & (~15));
  int frameSize = wAlign16 * hAlign16 * 3 / 2;
  int dmafd = dmaFd;
  uint32_t handles[4], pitches[4], offsets[4];

  if (DRM_FORMAT_NV12 != fmt)
    return -1;

#if 0
    //create bo
#if 1
    if (!pDrmDsp->bo[0]) {
      printf("%s:bo widthxheight:%dx%d\n", __func__, wAlign16, hAlign16);
      pDrmDsp->bo[0] = create_sp_bo(pDrmDsp->dev, wAlign16, hAlign16,
                                    16, 32, DRM_FORMAT_NV12, 0);
      pDrmDsp->bo[1] = create_sp_bo(pDrmDsp->dev, wAlign16, hAlign16,
                                    16, 32, DRM_FORMAT_NV12, 0);
      if (!pDrmDsp->bo[0] || !pDrmDsp->bo[1]) {
        printf("%s:create bo failed ! \n", __func__);
        return -1;
      }
      pDrmDsp->nextbo = pDrmDsp->bo[0];
    }
  
    if (!pDrmDsp->nextbo) {
      printf("%s:no available bo ! \n", __func__);
      return -1;
    }
  
    bo = pDrmDsp->nextbo;
#else
    bo = create_sp_bo(pDrmDsp->dev, wAlign16, hAlign16,
                      16, 32, DRM_FORMAT_NV12, 0);
    if (!bo)
      printf("%s:create bo failed ! \n", __func__);
#endif

  handles[0] = bo->handle;
  pitches[0] = wAlign16;
  offsets[0] = 0;
  handles[1] = bo->handle;
  pitches[1] = wAlign16;
  offsets[1] = width * height; //wAlign16 * hAlign16;
  //copy src data to bo
  memcpy(bo->map_addr, (void*)dmaFd, wAlign16 * hAlign16 * 3 / 2);

  ret = drmModeAddFB2(bo->dev->fd, bo->width, bo->height,
                      bo->format, handles, pitches, offsets,
                      &bo->fb_id, bo->flags);
  if (ret) {
    printf("%s:failed to create fb ret=%d\n", __func__, ret);
    printf("fd:%d ,wxh:%ux%u,format:%u,handles:%u,%u,pictches:%u,%u,offsets:%u,%u,fb_id:%u,flags:%u \n",
           bo->dev->fd, bo->width, bo->height, bo->format,
           handles[0], handles[1], pitches[0], pitches[1],
           offsets[0], offsets[1], bo->fb_id, bo->flags);
    return ret;
  }
  printf("addfb2: fd:%d ,wxh:%ux%u,format:%u,handles:%u,%u,pictches:%u,%u,offsets:%u,%u,fb_id:%u,flags:%u \n",
		 bo->dev->fd, bo->width, bo->height, bo->format,
		 handles[0], handles[1], pitches[0], pitches[1],
		 offsets[0], offsets[1], bo->fb_id, bo->flags);

  printf ("drmModeSetPlane at (%i,%i) %ix%i sourcing at (%i,%i) %ix%i",
      0,0,pDrmDsp->test_crtc->crtc->mode.hdisplay,pDrmDsp->test_crtc->crtc->mode.vdisplay,
      0,0, width, height);

  ret = drmModeSetPlane(pDrmDsp->dev->fd, pDrmDsp->test_plane->plane->plane_id,
                        pDrmDsp->test_crtc->crtc->crtc_id, bo->fb_id, 0, 0, 0,
                        pDrmDsp->test_crtc->crtc->mode.hdisplay,
                        pDrmDsp->test_crtc->crtc->mode.vdisplay,
                        0, 0, width << 16, height << 16);
  if (ret) {
    printf("failed to set plane to crtc ret=%d\n", ret);
    return ret;
  }
    //free_sp_bo(bo);
#if 0
  if (pDrmDsp->test_plane->bo) {
    if (pDrmDsp->test_plane->bo->fb_id) {
      ret = drmModeRmFB(pDrmDsp->dev->fd, pDrmDsp->test_plane->bo->fb_id);
      if (ret)
        printf("Failed to rmfb ret=%d!\n", ret);
    }
    if (pDrmDsp->test_plane->bo->handle) {
      struct drm_gem_close req = {
        .handle = pDrmDsp->test_plane->bo->handle,
      };

      drmIoctl(bo->dev->fd, DRM_IOCTL_GEM_CLOSE, &req);
      printf("%s:close bo success!\n", __func__);
    }

    if (!pDrmDsp->nextbo)
      free_sp_bo(pDrmDsp->test_plane->bo);
  }
  pDrmDsp->test_plane->bo = bo; //last po
#endif
#if 1
  //switch bo
  if (pDrmDsp->nextbo == pDrmDsp->bo[0])
    pDrmDsp->nextbo = pDrmDsp->bo[1];
  else
    pDrmDsp->nextbo = pDrmDsp->bo[0];
#endif
#else
  bo = bo_list_search(pDrmDsp, dmaFd);
  if (!bo) {
    bo = calloc(1, sizeof(*bo));
    if (!bo)
      return NULL;
    memset(bo, 0, sizeof(*bo));
	memset(handles, 0, sizeof(handles));
	memset(pitches, 0, sizeof(pitches));
	memset(offsets, 0, sizeof(offsets));

    ret = drmPrimeFDToHandle(pDrmDsp->dev->fd, dmaFd, &bo->handle);
	if (ret) {
		printf("drmPrimeFDToHandle failed, dmaFd %d, ret %d\n", dmaFd, ret);
		exit(-1);
	}
    bo->dev = pDrmDsp->dev;
    bo->width = wAlign16;
    bo->height = hAlign16;
    bo->depth = 16;
    bo->bpp = 32;
    bo->format = DRM_FORMAT_NV12;
    bo->flags = 0;
    bo->fd = dmaFd;

    handles[0] = bo->handle;
    pitches[0] = bo->width;
    offsets[0] = 0;
    handles[1] = bo->handle;
    pitches[1] = bo->width;
    offsets[1] = bo->width * bo->height;

    printf("addfb2: fd:%d ,wxh:%ux%u,format:%u,handles:%u,%u,pictches:%u,%u,offsets:%u,%u,fb_id:%u,flags:%u \n",
         bo->dev->fd, bo->width, bo->height, bo->format,
         handles[0], handles[1], pitches[0], pitches[1],
         offsets[0], offsets[1], bo->fb_id, bo->flags);

    ret = drmModeAddFB2(bo->dev->fd, bo->width, bo->height,
    				bo->format, handles, pitches, offsets,
    				&bo->fb_id, bo->flags);
    if (ret) {
      printf("failed to addfb2, dmafd %d, ret=%d\n",dmaFd, ret);
      exit(-1);
    }
  }
  printf ("drmModeSetPlane at (%i,%i) %ix%i sourcing at (%i,%i) %ix%i \n",
      0,0,pDrmDsp->test_crtc->crtc->mode.hdisplay,pDrmDsp->test_crtc->crtc->mode.vdisplay,
      0,0, width, height);
  ret = drmModeSetPlane(pDrmDsp->dev->fd, pDrmDsp->test_plane->plane->plane_id,
  				  pDrmDsp->test_crtc->crtc->crtc_id, bo->fb_id, 0, 0, 0,
  				  pDrmDsp->test_crtc->crtc->mode.hdisplay,
  				  pDrmDsp->test_crtc->crtc->mode.vdisplay,
  				  0, 0, bo->width << 16, bo->height << 16);

  bo_list_add_head(pDrmDsp, bo);
#endif
}
