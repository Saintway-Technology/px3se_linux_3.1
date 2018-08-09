#ifndef __VEHICLE_AD_7180_H__
#define __VEHICLE_AD_7180_H__

extern struct ad_dev *g_addev;

int adv7180_ad_init(struct ad_dev *ad);
int adv7180_ad_deinit(void);
int adv7180_ad_get_cfg(struct vehicle_cfg **cfg);
void adv7180_ad_check_cif_error(struct ad_dev *ad, int last_line);
int adv7180_check_id(struct ad_dev *ad);

#endif

