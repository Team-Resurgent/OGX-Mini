#ifndef _SWITCH_PRO_HOST_H_
#define _SWITCH_PRO_HOST_H_

#include <cstdint>

#include "Descriptors/SwitchPro.h"
#include "USBHost/HostDriver/HostDriver.h"

class SwitchProHost : public HostDriver
{
public:
    SwitchProHost(uint8_t idx)
        : HostDriver(idx) {}

    void initialize(Gamepad& gamepad, uint8_t address, uint8_t instance, const uint8_t* report_desc, uint16_t desc_len) override;
    void process_report(Gamepad& gamepad, uint8_t address, uint8_t instance, const uint8_t* report, uint16_t len) override;
    bool send_feedback(Gamepad& gamepad, uint8_t address, uint8_t instance) override;

private:
    enum class InitState
    {
        HANDSHAKE,
        TIMEOUT,
        FULL_REPORT,
        LED,
        LED_HOME,
        IMU,
        DONE
    };

    InitState init_state_{InitState::HANDSHAKE};
    uint8_t sequence_counter_{0};

    SwitchPro::InReport prev_in_report_{};
    SwitchPro::OutReport out_report_{};

    void init_switch_host(Gamepad& gamepad, uint8_t address, uint8_t instance);
    // bool send_handshake(uint8_t address, uint8_t instance);
    // bool disable_timeout(uint8_t address, uint8_t instance);
    uint8_t get_output_sequence_counter();

    static inline int16_t normalize_axis(uint16_t value)
    {
        /*  12bit value from the controller doesnt cover the full 12bit range seemingly
            isn't completely centered at 2047 either so I may be missing something here
            tried to get as close as possible with the multiplier */

        int32_t normalized_value = (value - 2047) * 22;

        if (normalized_value < INT16_MIN) 
        {
            return INT16_MIN;
        } 
        else if (normalized_value > INT16_MAX) 
        {
            return INT16_MAX;
        }

        return static_cast<int16_t>(normalized_value); 
    }
};

#endif // _SWITCH_PRO_HOST_H_