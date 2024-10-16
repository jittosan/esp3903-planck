import time
import numpy as np
import rp

#? Possible waveforms:
#?   RP_WAVEFORM_SINE, RP_WAVEFORM_SQUARE, RP_WAVEFORM_TRIANGLE, RP_WAVEFORM_RAMP_UP,
#?   RP_WAVEFORM_RAMP_DOWN, RP_WAVEFORM_DC, RP_WAVEFORM_PWM, RP_WAVEFORM_ARBITRARY,
#?   RP_WAVEFORM_DC_NEG, RP_WAVEFORM_SWEEP

channel = rp.RP_CH_1        # rp.RP_CH_2
channel2 = rp.RP_CH_2
waveform = rp.RP_WAVEFORM_ARBITRARY
freq = 10000
ampl = 1

N = 16384       # Number of samples in the buffer

##### Custom waveform setup #####
x = rp.arbBuffer(N)
y = rp.arbBuffer(N)

t = np.linspace(0, 1, N)*2*np.pi

x_temp = np.sin(t) + 1/3*np.sin(3*t)
y_temp = 1/2*np.sin(t) + 1/4*np.sin(4*t)

for i in range(0, N, 1):
    x[i] = float(x_temp[i])
    y[i] = float(y_temp[i])


# Initialize the interface
rp.rp_Init()

# Reset generator
rp.rp_GenReset()

###### Generation #####
rp.rp_GenWaveform(channel, waveform)
rp.rp_GenArbWaveform(channel, x.cast(), N)
rp.rp_GenFreqDirect(channel, freq)
rp.rp_GenAmp(channel, ampl)

rp.rp_GenWaveform(channel2, waveform)
rp.rp_GenArbWaveform(channel2, y.cast(), N)
rp.rp_GenFreqDirect(channel2, freq)
rp.rp_GenAmp(channel2, ampl)

#? Possible trigger sources:
#?   RP_GEN_TRIG_SRC_INTERNAL, RP_GEN_TRIG_SRC_EXT_PE, RP_GEN_TRIG_SRC_EXT_NE

# Specify generator trigger source
rp.rp_GenTriggerSource(channel, rp.RP_GEN_TRIG_SRC_INTERNAL)

# Enable output synchronisation
rp.rp_GenOutEnableSync(True)

# Syncronise output channels
rp.rp_GenSynchronise()


# Release resources
rp.rp_Release()