#pragma once

#include "pinouts.h"
#include "color.h"

const char* cargoId     = "001";
const char* wareHouseId = "100";


// <?xml version="1-0"
// encoding="UTF-8"?>
// <cargo>

// <cargo cargoID="005">
// <color>BLUE</color>
// ‹location>02</location>
// ‹name>television</name>
// <warehouseID>100</warehouseID>
// </cargo>
// <cargo cargoID="006">
// <color>YELLOW</color>
// <location>03</location>
// <name>AC</name>
// <warehouseID>100</warehouseID>
// </cargo>
// </cargo>

// <cargo cargoID="004">
// <color>RED</color>
// <location>01</location>
// <name>computer</name>
// <warehouseID>100</warehouseID>
// </cargo>

char xmlInfo[200]{};

void testSend(){
  Serial.write("testing...\n");
}

void sendInfo(const int color, const int location) {
  memset(xmlInfo, '\0', sizeof(xmlInfo));

  sprintf(xmlInfo,
          "<cargo "
          "cargoID=\"%s\">\n<color>%s</color>\n<location>0%d</location>\n<name>computer</"
          "name>\n<warehouseID>%s</warehouseID>\n</cargo>",
          cargoId, colorLookupArray[color], location, wareHouseId);
  Serial.write(xmlInfo);
}