int count = 0;
// 包头
typedef struct f_head
{
  uint8_t head = 0xe0;    // 头部
  uint32_t sequence = 0;  // 流水号
  uint8_t type = 0;       // 类型
  uint32_t length = 0;        // 消息体 长度
} f_head;


// 注册
typedef struct f_00
{
  uint8_t model;         // 设备型号
  char macAddress[10];     // 设备Mac地址
} f_00;

// 注册回应
typedef struct f_f0
{
  uint8_t status;         // 设备型号
  char token[16] ;         // Token
} f_f0;

// 温度
typedef struct f_05
{
  uint8_t temperature0;    // 小数部分
  int8_t temperature1;     // 整数部分
} f_05;

// 湿度
typedef struct f_06
{
  uint8_t humidity0;    // 小数部分
  int8_t humidity1;     // 整数部分
} f_06;

void handSequence() {
  if (count > 100) {
    count = 0;
  }
}

