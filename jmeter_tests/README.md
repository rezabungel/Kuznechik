# JMeter Load Testing

## Start services
Start InfluxDB and Grafana:

```bash
docker compose up
```

## Grafana dashboard
Dashboard is available at [link](https://grafana.com/grafana/dashboards/5496/).

## Run test
Run JMeter test plan using configuration from `user.properties`:

```bash
bash run_jmeter_test.sh
```

JMeter logs are saved in `.jmeter_logs/`, test results in `.jmeter_results/`. Metrics are available in Grafana.
