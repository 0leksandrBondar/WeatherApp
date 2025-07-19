# ☀️ WeatherApp

A simple C++ console application to fetch the current weather for a given city using the [wttr.in](https://wttr.in) API. The app supports caching, forced refresh, error handling, and clean CLI output.

---

## 🔧 Build Instructions

### Libs:

- CMake >= 3.16
- C++17 or later
- `libcurl`
- `nlohmann/json` (included as header-only)
- `argparse` (included as header-only)

### Build Steps:

```bash
git clone https://github.com/yourname/WeatherApp.git
cd WeatherApp
mkdir build && cd build
cmake ..
make
```

> After building, the executable `WeatherApp` will be created.

---

## ▶️ Usage

```bash
./WeatherApp [city] [--refresh]
```

### Options:

- `city` — the city name (e.g., `London`, `Berlin`, `Kyiv`)
- `--refresh` — (optional) forces API fetch even if cached data is available
- `--help` — shows usage info

### Examples:

```bash
./WeatherApp
```

> Auto-detects city based on IP (if supported).

```bash
./WeatherApp Lviv
```

> Fetches weather for "Lviv" using cached data if available.

```bash
./WeatherApp Kyiv --refresh
```

> Forces fetching the latest weather for "Kyiv".

---

## 🧪 Features

- ❄️ **Caching**: weather data is cached per city name
- 📂 **Refresh Control**: use `--refresh` to ignore cached data
- 🔀 **Auto-detect City**: when city is not provided, the API suggests a location
- ⚠️ **Error Handling**: user-friendly messages when API fails or JSON is invalid

---

## 🌐 API Info

- Uses `https://wttr.in/<city>?format=j1` endpoint to fetch JSON-formatted weather.

---

## 📄 License

MIT License. Free to use, modify, and distribute.

