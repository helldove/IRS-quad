#ifndef _PWM_DRIVER_
#define _PWM_DRIVER_

#define PWM_CHANNELS		2
#define BASEADDR			0x01C20C00
#define CTRLADDR			0x200
#define CH0PERIOD			0x204
#define CH1PERIOD			0x208

struct pwm_device;

struct pwm_device *pwm_request(int pwm_id, const char *label);
void pwm_free(struct pwm_device *pwm);
int pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns);
int pwm_enable(struct pwm_device *pwm);
void pwm_disable(struct pwm_device *pwm);

#endif