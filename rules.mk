# User settings
LEADER_ENABLE = no      # Enable leader keys
OLED_DRIVER_ENABLE = yes # Enables the use of OLED displays
COMBO_ENABLE = yes       # Enables combos

# Save firmware space
MOUSEKEY_ENABLE = no
MAGIC_ENABLE = no
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
ENCODER_ENABLE = no       # Enables the use of one or more encoders
RGBLIGHT_ENABLE = no      # Enable keyboard RGB underglow

SRC += features/casemodes.c
SRC += features/leader.c
include $(KEYBOARD_PATH_2)/keymaps/$(KEYMAP)/qmk-vim/rules.mk

# If flashing the right side
RIGHT = 0
ifeq ($(RIGHT), 1)
	OLED_DRIVER_ENABLE = no   # Disables the use of OLED displays
	CFLAGS += "-D MY_SPLIT_RIGHT"
endif
