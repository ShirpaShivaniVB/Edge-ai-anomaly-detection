#pragma once
#include "driver/adc.h"
#include "driver/gpio.h"

/* ── WiFi ───────────────────────────────────── */
#define WIFI_SSID              "your_wifi_ssid"
#define WIFI_PASSWORD          "your_wifi_password"

/* ── MQTT ───────────────────────────────────── */
#define MQTT_BROKER_URI        "mqtt://broker.hivemq.com"
#define MQTT_ALERT_TOPIC       "anomaly_detection/alerts"

/* ── Sensor ADC ─────────────────────────────── */
#define SENSOR_ADC_CHANNEL     ADC1_CHANNEL_6   /* GPIO34 */

/* ── TFLite Model ───────────────────────────── */
#define TENSOR_ARENA_SIZE      (32 * 1024)      /* 32 KB — adjust if needed */
#define FEATURE_LENGTH         16               /* Input window size */

/* ── Preprocessing (from train_and_convert.py output) ── */
#define ADC_MEAN               2048.0f          /* Replace with actual mean */
#define ADC_STD                512.0f           /* Replace with actual std  */

/* ── Anomaly Detection ──────────────────────── */
#define ANOMALY_THRESHOLD      0.015000f        /* Replace with output of train script */

/* ── GPIO ───────────────────────────────────── */
#define ALERT_LED_GPIO         GPIO_NUM_2

/* ── Timing ─────────────────────────────────── */
#define SAMPLE_INTERVAL_MS     50               /* 20 Hz sampling rate */
