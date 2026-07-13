#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11   // đổi thành DHT22 nếu dùng loại đó

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);  // DHT cần tối thiểu 1-2s giữa các lần đọc, đọc nhanh hơn sẽ lỗi

  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();

  if (isnan(humidity) || isnan(tempC)) {
    Serial.println("Đọc cảm biến thất bại!");
    return;
  }

  Serial.print("Độ ẩm: ");
  Serial.print(humidity);
  Serial.print("%  Nhiệt độ: ");
  Serial.print(tempC);
  Serial.println("°C");
}
