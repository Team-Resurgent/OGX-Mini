#pragma once

#include <stdint.h>

#define HID_ENDPOINT_SIZE 64

/**************************************************************************
 *
 *  Endpoint Buffer Configuration
 *
 **************************************************************************/

#define ENDPOINT0_SIZE	64

#define GAMEPAD_INTERFACE	0
#define GAMEPAD_ENDPOINT	1
#define GAMEPAD_SIZE		64

#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)

#define PS3_HAT_UP        0x00
#define PS3_HAT_UPRIGHT   0x01
#define PS3_HAT_RIGHT     0x02
#define PS3_HAT_DOWNRIGHT 0x03
#define PS3_HAT_DOWN      0x04
#define PS3_HAT_DOWNLEFT  0x05
#define PS3_HAT_LEFT      0x06
#define PS3_HAT_UPLEFT    0x07
#define PS3_HAT_NOTHING   0x08

#define PS3_MASK_SQUARE   (1U <<  0)
#define PS3_MASK_CROSS    (1U <<  1)
#define PS3_MASK_CIRCLE   (1U <<  2)
#define PS3_MASK_TRIANGLE (1U <<  3)
#define PS3_MASK_L1       (1U <<  4)
#define PS3_MASK_R1       (1U <<  5)
#define PS3_MASK_L2       (1U <<  6)
#define PS3_MASK_R2       (1U <<  7)
#define PS3_MASK_SELECT   (1U <<  8)
#define PS3_MASK_START    (1U <<  9)
#define PS3_MASK_L3       (1U << 10)
#define PS3_MASK_R3       (1U << 11)
#define PS3_MASK_PS       (1U << 12)
#define PS3_MASK_TP       (1U << 13)

#define PS3_JOYSTICK_MIN 0x00
#define PS3_JOYSTICK_MID 0x80
#define PS3_JOYSTICK_MAX 0xFF

typedef struct __attribute((packed, aligned(1)))
{
    uint8_t report_id;
    uint8_t unk0;

    uint8_t select : 1;
    uint8_t l3     : 1;
    uint8_t r3     : 1;
    uint8_t start  : 1;
    uint8_t up     : 1;
    uint8_t right  : 1;
    uint8_t down   : 1;
    uint8_t left   : 1;

    uint8_t l2       : 1;
    uint8_t r2       : 1;
    uint8_t l1       : 1;
    uint8_t r1       : 1;
    uint8_t triangle : 1;
    uint8_t circle   : 1;
    uint8_t cross    : 1;
    uint8_t square   : 1;

    uint8_t ps : 1;
    uint8_t    : 0;

    uint8_t unknown1;

    uint8_t left_x;
    uint8_t left_y;
    uint8_t right_x;
    uint8_t right_y;

	uint8_t unknown2[4];

	uint8_t up_axis;
	uint8_t right_axis;
	uint8_t down_axis;
	uint8_t left_axis;

	uint8_t l2_axis;
	uint8_t r2_axis;
	uint8_t l1_axis;
	uint8_t r1_axis;

	uint8_t triangle_axis;
	uint8_t circle_axis;
	uint8_t cross_axis;
	uint8_t square_axis;

    uint8_t unknown3[15];

    int16_t acceler_x;
    int16_t acceler_y;
    int16_t acceler_z;

    int16_t velocity_z;
} DualShock3Report;

struct sixaxis_led {
	uint8_t time_enabled; /* the total time the led is active (0xff means forever) */
	uint8_t duty_length;  /* how long a cycle is in deciseconds (0 means "really fast") */
	uint8_t enabled;
	uint8_t duty_off; /* % of duty_length the led is off (0xff means 100%) */
	uint8_t duty_on;  /* % of duty_length the led is on (0xff mean 100%) */
} __attribute__((packed));

struct sixaxis_rumble {
	uint8_t padding;
	uint8_t right_duration; /* Right motor duration (0xff means forever) */
	uint8_t right_motor_on; /* Right (small) motor on/off, only supports values of 0 or 1 (off/on) */
	uint8_t left_duration;    /* Left motor duration (0xff means forever) */
	uint8_t left_motor_force; /* left (large) motor, supports force values from 0 to 255 */
} __attribute__((packed));

struct sixaxis_output_report {
	struct sixaxis_rumble rumble;
	uint8_t padding[4];
	uint8_t leds_bitmap; /* bitmap of enabled LEDs: LED_1 = 0x02, LED_2 = 0x04, ... */
	struct sixaxis_led led[4];    /* LEDx at (4 - x) */
	struct sixaxis_led _reserved; /* LED5, not actually soldered */
} __attribute__((packed));

static const uint8_t ps3_string_language[]     = { 0x09, 0x04 };
static const uint8_t ps3_string_manufacturer[] = "Sony";
static const uint8_t ps3_string_product[]      = "PLAYSTATION(R)3 Controller";
static const uint8_t ps3_string_version[]      = "1.0";

static const uint8_t *ps3_string_descriptors[] __attribute__((unused)) =
{
	ps3_string_language,
	ps3_string_manufacturer,
	ps3_string_product,
	ps3_string_version
};

static const uint8_t ps3_device_descriptor[] =
{
	0x12,        // bLength
	0x01,        // bDescriptorType (Device)
	0x00, 0x02,  // bcdUSB 2.00
	0x00,        // bDeviceClass (Use class information in the Interface Descriptors)
	0x00,        // bDeviceSubClass 
	0x00,        // bDeviceProtocol 
	0x40,        // bMaxPacketSize0 64
	0x4C, 0x05,  // idVendor 0x054C
	0x68, 0x02,  // idProduct 0x0268
	0x00, 0x01,  // bcdDevice 2.00
	0x01,        // iManufacturer (String Index)
	0x02,        // iProduct (String Index)
	0x00,        // iSerialNumber (String Index)
	0x01,        // bNumConfigurations 1
};

static const uint8_t ps3_report_descriptor[] =
{
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x04,        // Usage (Joystick)
	0xA1, 0x01,        // Collection (Application)
	0xA1, 0x02,        //   Collection (Logical)
	0x85, 0x01,        //     Report ID (1)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x01,        //     Report Count (1)
	0x15, 0x00,        //     Logical Minimum (0)
	0x26, 0xFF, 0x00,  //     Logical Maximum (255)
	0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x01,        //     Report Size (1)
	0x95, 0x13,        //     Report Count (19)
	0x15, 0x00,        //     Logical Minimum (0)
	0x25, 0x01,        //     Logical Maximum (1)
	0x35, 0x00,        //     Physical Minimum (0)
	0x45, 0x01,        //     Physical Maximum (1)
	0x05, 0x09,        //     Usage Page (Button)
	0x19, 0x01,        //     Usage Minimum (0x01)
	0x29, 0x13,        //     Usage Maximum (0x13)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x01,        //     Report Size (1)
	0x95, 0x0D,        //     Report Count (13)
	0x06, 0x00, 0xFF,  //     Usage Page (Vendor Defined 0xFF00)
	0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x15, 0x00,        //     Logical Minimum (0)
	0x26, 0xFF, 0x00,  //     Logical Maximum (255)
	0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
	0x09, 0x01,        //     Usage (Pointer)
	0xA1, 0x00,        //     Collection (Physical)
	0x75, 0x08,        //       Report Size (8)
	0x95, 0x04,        //       Report Count (4)
	0x35, 0x00,        //       Physical Minimum (0)
	0x46, 0xFF, 0x00,  //       Physical Maximum (255)
	0x09, 0x30,        //       Usage (X)
	0x09, 0x31,        //       Usage (Y)
	0x09, 0x32,        //       Usage (Z)
	0x09, 0x35,        //       Usage (Rz)
	0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              //     End Collection
	0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x27,        //     Report Count (39)
	0x09, 0x01,        //     Usage (Pointer)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x30,        //     Report Count (48)
	0x09, 0x01,        //     Usage (Pointer)
	0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x30,        //     Report Count (48)
	0x09, 0x01,        //     Usage (Pointer)
	0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,              //   End Collection
	0xA1, 0x02,        //   Collection (Logical)
	0x85, 0x02,        //     Report ID (2)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x30,        //     Report Count (48)
	0x09, 0x01,        //     Usage (Pointer)
	0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,              //   End Collection
	0xA1, 0x02,        //   Collection (Logical)
	0x85, 0xEE,        //     Report ID (-18)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x30,        //     Report Count (48)
	0x09, 0x01,        //     Usage (Pointer)
	0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,              //   End Collection
	0xA1, 0x02,        //   Collection (Logical)
	0x85, 0xEF,        //     Report ID (-17)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x30,        //     Report Count (48)
	0x09, 0x01,        //     Usage (Pointer)
	0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,              //   End Collection
	0xC0,              // End Collection
};

static const uint8_t ps3_hid_descriptor[] =
{
	0x09,        // bLength
	0x21,        // bDescriptorType (HID)
	0x11, 0x01,  // bcdHID 1.11
	0x00,        // bCountryCode
	0x01,        // bNumDescriptors
	0x22,        // bDescriptorType[0] (HID)
	0x94, 0x00,  // wDescriptorLength[0] 148
};

// #define CONFIG1_DESC_SIZE		(9+9+9+7)
static const uint8_t ps3_configuration_descriptor[] =
{
	0x09,        // bLength
	0x02,        // bDescriptorType (Configuration)
	0x29, 0x00,  // wTotalLength 41
	0x01,        // bNumInterfaces 1
	0x01,        // bConfigurationValue
	0x00,        // iConfiguration (String Index)
	0x80,        // bmAttributes
	0xFA,        // bMaxPower 500mA

	0x09,        // bLength
	0x04,        // bDescriptorType (Interface)
	0x00,        // bInterfaceNumber 0
	0x00,        // bAlternateSetting
	0x02,        // bNumEndpoints 2
	0x03,        // bInterfaceClass
	0x00,        // bInterfaceSubClass
	0x00,        // bInterfaceProtocol
	0x00,        // iInterface (String Index)

	0x09,        // bLength
	0x21,        // bDescriptorType (HID)
	0x10, 0x01,  // bcdHID 1.10
	0x00,        // bCountryCode
	0x01,        // bNumDescriptors
	0x22,        // bDescriptorType[0] (HID)
	0x94, 0x00,  // wDescriptorLength[0] 148

	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x81,        // bEndpointAddress (IN/D2H)
	0x03,        // bmAttributes (Interrupt)
	0x40, 0x00,  // wMaxPacketSize 64
	0x0A,        // bInterval 10 (unit depends on device speed)

	0x07,        // bLength
	0x05,        // bDescriptorType (Endpoint)
	0x02,        // bEndpointAddress (OUT/H2D)
	0x03,        // bmAttributes (Interrupt)
	0x40, 0x00,  // wMaxPacketSize 64
	0x0A,        // bInterval 10 (unit depends on device speed)
};