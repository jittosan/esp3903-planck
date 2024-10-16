import redpitaya_scpi as scpi
import numpy as np
import time
import csv

# -----------------------------
# Configuration Parameters
# -----------------------------
# RP_IP = 'rp-FFFEA1.local'         # Replace with your Red Pitaya's hostname or IP address
RP_IP = '169.254.47.245'         # Replace with your Red Pitaya's hostname or IP address
DC_VOLTAGE = 2.5                      # Desired DC voltage for OUT1 (in volts)
DURATION = 5                          # Duration for the measurement (in seconds)
CSV_FILENAME = 'dc_voltage_data.csv'   # Output CSV file name
SAMPLING_RATE = 100                   # Samples per second (Hz)

# -----------------------------
# Establish SCPI Connection
# -----------------------------

try:
    rp = scpi.scpi(RP_IP)
    print(f"Connected to Red Pitaya at {RP_IP}.")
except Exception as e:
    print(f"Failed to connect to Red Pitaya at {RP_IP}: {e}")
    sys.exit(1)

# -----------------------------
# Configure Built-In DC Waveform on OUT1
# -----------------------------

print("Configuring OUT1 for DC output...")

# Reset the signal generator to default settings
rp.tx_txt("GEN:RST")

# Select DC waveform
rp.tx_txt("GEN:FUNC DC")

# Set DC voltage amplitude and offset
# Assuming DAC range is 0V to 3.3V
# For DC, amplitude is half the desired DC voltage and offset is half the desired DC voltage
# To output DC voltage V, set amplitude to V and offset to 0
rp.tx_txt(f"GEN:VOLT {DC_VOLTAGE}")  # Set DC voltage
rp.tx_txt("GEN:OFFS 0")              # No offset needed for pure DC

# Start the signal generator
rp.tx_txt("GEN:STAT ON")

time.sleep(10)
print(f"OUT1 configured to output {DC_VOLTAGE} V DC.")