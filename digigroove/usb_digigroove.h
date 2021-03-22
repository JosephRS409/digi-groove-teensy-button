#ifndef USBdigigroove_h_
#define USBdigigroove_h_

#include "usb_desc.h"

#if defined(DIGIGROOVE_P1_INTERFACE) || defined(DIGIGROOVE_P2_ENDPOINT)

#include <inttypes.h>

// C language implementation
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
int usb_digigroove_send(bool p1);
extern uint8_t usb_digigroove_data[DIGIGROOVE_SIZE * 2]; // two sides
#ifdef __cplusplus
}
#endif

// C++ interface
#ifdef __cplusplus
class usb_digigroove_class
{
	private:
	static uint8_t manual_mode;

        public:
        void begin(void) { }
        void end(void) { }
	void button(uint8_t button, bool val, bool p1) {
		uint8_t idx = p1 ? 0 : DIGIGROOVE_SIZE;
		if (--button >= 8) return;
		if (val) usb_digigroove_data[idx] |= (1 << button);
		else usb_digigroove_data[idx] &= ~(1 << button);
		if (!manual_mode) {
			usb_digigroove_send(true);
			usb_digigroove_send(false);
		}
	}
	void useManualSend(bool mode) {
		manual_mode = mode;
	}
	void send_now(void) {
		usb_digigroove_send(true);
		usb_digigroove_send(false);
	}
};
extern usb_digigroove_class Digigroove;

#endif // __cplusplus

#endif // digigroove endpoint defined

#endif // USBdigigroove_h_

