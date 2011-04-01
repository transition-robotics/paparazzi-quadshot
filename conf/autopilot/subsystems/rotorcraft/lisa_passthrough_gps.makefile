#
#
# Using the STM32 as IO processor
#
#

SRC_ARCH=arch/$(ARCH)
SRC_LISA=lisa
SRC_LISA_ARCH=$(SRC_LISA)/arch/$(ARCH)

# Link Overo
ap.CFLAGS += -DUSE_OVERO_LINK -I$(SRC_LISA) -I$(SRC_LISA_ARCH)
ap.CFLAGS += -DOVERO_LINK_MSG_UP=AutopilotMessageGPSUp
ap.CFLAGS += -DOVERO_LINK_MSG_DOWN=AutopilotMessageGPSDown
ap.CFLAGS += -DOVERO_LINK_LED_OK=3 -DOVERO_LINK_LED_KO=2 -DUSE_DMA1_C2_IRQ
ap.srcs += $(SRC_LISA)/lisa_overo_link.c           \
            $(SRC_LISA_ARCH)/lisa_overo_link_arch.c
