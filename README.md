# Edge AI–Based Anomaly Detection System

On-device anomaly detection running entirely on **ESP32** using **TensorFlow Lite for Microcontrollers** and **FreeRTOS**. A Python-trained autoencoder is quantised and embedded in firmware — no cloud round-trip for inference, only anomaly alerts are transmitted via MQTT.

---

## How It Works

An **autoencoder** is trained on normal sensor data. It learns to reconstruct normal patterns accurately. When given anomalous input, the reconstruction error spikes above a threshold — indicating an anomaly.

```
Sensor → Sliding Window → Normalise → TFLite Inference → Reconstruction Error → Alert?
```

All inference runs **on the ESP32** — eliminating cloud latency and reducing bandwidth.

---

## Features

- Autoencoder trained in Python, quantised to int8 TFLite model
- On-device inference using TensorFlow Lite for Microcontrollers
- RTOS task architecture: sensor task + inference task
- MQTT alert published only when anomaly detected
- LED alert on GPIO2 for local indication
- Full model training + conversion script included (`train_and_convert.py`)

---

## Project Structure

```
edge-ai-anomaly-detection/
├── main.c                  # ESP32 firmware (FreeRTOS + TFLite)
├── config.h                # All configuration constants
├── model_data.h            # Generated TFLite model as C array
├── train_and_convert.py    # Python: train autoencoder + export to TFLite
└── README.md
```

---

## Hardware Required

| Component | Details |
|-----------|---------|
| Microcontroller | ESP32 DevKit V1 |
| Sensor | Any analog sensor (vibration, temperature, pressure) |
| LED | GPIO2 (onboard LED) |

---

## Setup

### Step 1 — Train the model (on your PC)

```bash
pip install tensorflow pandas numpy

# Prepare sensor_data.csv with column: sensor_value
python train_and_convert.py --data sensor_data.csv --output model_data.h
```

The script outputs:
- `model_data.h` → copy to project folder
- Threshold and normalisation values → update `config.h`

### Step 2 — Flash to ESP32

```bash
git clone https://github.com/ShirpaShivaniVB/edge-ai-anomaly-detection
cd edge-ai-anomaly-detection

# Copy generated model_data.h here
# Update config.h with threshold, ADC_MEAN, ADC_STD

idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

---

## MQTT Anomaly Alert Payload

```json
{
  "anomaly": true,
  "recon_error": 0.0312,
  "f0": 0.452,
  "f1": -0.231,
  "f2": 0.879
}
```

---

## Architecture

```
app_main()
    ├── tflite_init()      → loads quantised model into tensor arena
    ├── wifi_init()        → WiFi connection
    ├── mqtt_init()        → MQTT broker connection
    │
    ├── sensor_task        → reads ADC at 20Hz → fills sliding window → queue
    └── inference_task     → preprocesses → TFLite invoke → checks threshold → alert
```

---

## Skills Demonstrated

`Embedded C` `FreeRTOS` `TensorFlow Lite` `ESP32` `Edge AI` `ADC` `MQTT` `Python` `Model Quantisation` `On-device ML`
