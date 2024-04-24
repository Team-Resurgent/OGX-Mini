#ifndef _N64USB_H_
#define _N64USB_H_

#include <stdint.h>

#include "usbh/GPHostDriver.h"

const usb_vid_pid_t n64_devices[] = 
{
    {0x0079, 0x0006} // Retrolink N64 USB gamepad
};

enum n64usb_dpad_mask
{
    N64_DPAD_MASK_UP = 0x00,
    N64_DPAD_MASK_UP_RIGHT = 0x01,
    N64_DPAD_MASK_RIGHT = 0x02,
    N64_DPAD_MASK_RIGHT_DOWN = 0x03,
    N64_DPAD_MASK_DOWN = 0x04,
    N64_DPAD_MASK_DOWN_LEFT = 0x05,
    N64_DPAD_MASK_LEFT = 0x06,
    N64_DPAD_MASK_LEFT_UP = 0x07,
    N64_DPAD_MASK_NONE = 0x08,
};

#define N64_DPAD_MASK    0x0F

#define N64_C_UP_MASK    (1 << 4)
#define N64_C_RIGHT_MASK (1 << 5)
#define N64_C_DOWN_MASK  (1 << 6)
#define N64_C_LEFT_MASK  (1 << 7)
#define N64_L_MASK       (1 << 8)
#define N64_R_MASK       (1 << 9)
#define N64_A_MASK       (1 << 10)
#define N64_Z_MASK       (1 << 11)
#define N64_B_MASK       (1 << 12)
#define N64_START_MASK   (1 << 13)

typedef struct __attribute__((packed))
{
    uint8_t x;
    uint8_t y;
    uint8_t padding[3];
    uint16_t buttons;
} N64USBReport;

struct N64USBState 
{
    uint8_t player_id = {0};
};

class N64USB: public GPHostDriver 
{
    public:
        ~N64USB() override {}

        virtual void init(uint8_t player_id, uint8_t dev_addr, uint8_t instance);
        virtual void process_hid_report(Gamepad* gamepad, uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len);
        virtual void process_xinput_report(Gamepad* gamepad, uint8_t dev_addr, uint8_t instance, xinputh_interface_t const* report, uint16_t len);
        virtual void hid_get_report_complete_cb(uint8_t dev_addr, uint8_t instance, uint8_t report_id, uint8_t report_type, uint16_t len);
        virtual bool send_fb_data(const Gamepad* gamepad, uint8_t dev_addr, uint8_t instance);
    private:
        N64USBState n64usb;
        void update_gamepad(Gamepad* gp, const N64USBReport* n64_data);
};

#endif // _N64USB_H_