
/*
task1: i am noticing the time to task1 and 3, counting the no of tasks
task2: in task2 i am noticing the time to task2, counting the no of tasks3
task3: Using all serial commands, 
task4: blinking leds on every batch completion
task5: showing task time on Oled1
task6: showing task time on Oled2
*/

#include <RTClib.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

RTC_DS1307 rtc; //here i am creating object of rtc
  DateTime start_time_batch1;
  DateTime end_time_batch1;
  DateTime start_time_batch2;
  DateTime end_time_batch2;
  DateTime start_time_batch3;
  DateTime end_time_batch3;
  DateTime start_time_task1;
  DateTime end_time_task1;
  DateTime start_time_task2;
  DateTime end_time_task2;
  DateTime start_time_task3;
  DateTime end_time_task3;

#define SDA_PIN_1  21
#define SCL_PIN_1  2
#define OLED_ADDR_1   0x3C


#define SDA_PIN_2  19
#define SCL_PIN_2  18
#define OLED_ADDR_2   0x3C


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define SCREEN_WIDTH2 128 
#define SCREEN_HEIGHT2 64 


Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR_1, SDA_PIN_1, SCL_PIN_1);
Adafruit_SSD1306 oled2(SCREEN_WIDTH2, SCREEN_HEIGHT2, &Wire, OLED_ADDR_2, SDA_PIN_2, SCL_PIN_2);




#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu=0;
#else 
static const BaseType_t app_cpu=1;
#endif
#define no_of_batches 3
#define Products_in_a_batch 10

//defined time for each task
#define task1_t 100
#define task2_t 300
#define task3_t 200

// initialized pins to indicate task completion
static const int led_pin1=4;
static const int led_pin2=0;
static const int led_pin3=2;


//initialized counters to count each task completion
int counter1=0;
int counter2=0;
int counter3=0;
int prod=0;
int batch_counter=0;

// initialized task handles
static TaskHandle_t task_1= NULL ;
static TaskHandle_t task_2= NULL ;
static TaskHandle_t task_3= NULL ;
static TaskHandle_t task_4= NULL ;
static TaskHandle_t task_5= NULL ;
static TaskHandle_t task_6= NULL ;

//funciton for task 1
void startTask1(void *parameter)
{
  
  while(1){
    counter1++;
if(counter1==1){
start_time_task1 = rtc.now();
}
  vTaskDelay( task1_t/ portTICK_PERIOD_MS);//time on task1
if (counter1==1){
end_time_task1 = rtc.now();
start_time_task3 = rtc.now();}
  vTaskDelay( task3_t/portTICK_PERIOD_MS);//time on task2
end_time_task3 = rtc.now();
  if (counter1 % Products_in_a_batch==0) // when a batch of 10 completes led pin will be set to high
  {
    counter1=0;
        

  }
  }
}

void startTask2(void *parameter){
  
 while(1){
  counter2++;
start_time_task2 = rtc.now();
  
 vTaskDelay( task2_t/ portTICK_PERIOD_MS);
 end_time_task2 = rtc.now();
 if (counter2 % Products_in_a_batch==0){
  
  counter2=0;



  }
}
}
void startTask3(void *parameter){
    int prevcount1=0;
    int prevcount2=0;
 while(1){
 
  if(prod==0 && counter1==0)
{start_time_batch1 = rtc.now();}
if (counter1==counter2 && counter1!=prevcount1 && counter2!=prevcount2) {
     prevcount1=counter1;
     prevcount2=counter2;

  Serial.print("C1:");
  Serial.println(counter1);
  Serial.print("C2:");
  Serial.println(counter2);
  
  prod++;
  
  Serial.print("Product: ");
  Serial.println(prod);


if (prod==(Products_in_a_batch*1))
{
  end_time_batch1 = rtc.now();
  start_time_batch2 = rtc.now();
}
if (prod==(Products_in_a_batch*2))
{
  end_time_batch2 = rtc.now();
  start_time_batch3 = rtc.now();
}
if (prod==(Products_in_a_batch*3))
{
  end_time_batch3 = rtc.now();
  
}
 if(prod%Products_in_a_batch==0)
 {

 batch_counter++;
 

 }
if (batch_counter==1 && prod==10 )
{ Serial.println("Batch One completed:");
  Serial.print("batch start time 1: ");
  Serial.print(start_time_batch1.hour(), DEC);
  Serial.print(':');
  Serial.print(start_time_batch1.minute(), DEC);
  Serial.print(':');
  Serial.print(start_time_batch1.second(), DEC);
  Serial.println();
  
  Serial.print("Batch End time 1: ");
  Serial.print(end_time_batch1.hour(), DEC);
  Serial.print(':');
  Serial.print(end_time_batch1.minute(), DEC);
  Serial.print(':');
  Serial.print(end_time_batch1.second(), DEC);
  Serial.println();
}
if (batch_counter==2 && prod==20)
{
  Serial.println("Batch 2 completed:");
  Serial.print("batch 2 start time : ");
  Serial.print(start_time_batch2.hour(), DEC);
  Serial.print(':');
  Serial.print(start_time_batch2.minute(), DEC);
  Serial.print(':');
  Serial.print(start_time_batch2.second(), DEC);
  Serial.println();
  
  Serial.print("Batch 2 End time : ");
  Serial.print(end_time_batch2.hour(), DEC);
  Serial.print(':');
  Serial.print(end_time_batch2.minute(), DEC);
  Serial.print(':');
  Serial.print(end_time_batch2.second(), DEC);
  Serial.println();

}
if (batch_counter==3 && prod==30)
{
  Serial.println("Batch 3 completed:");
  Serial.print("batch 3 start time : ");
  Serial.print(start_time_batch3.hour(), DEC);
  Serial.print(':');
  Serial.print(start_time_batch3.minute(), DEC);
  Serial.print(':');
  Serial.print(start_time_batch3.second(), DEC);
  Serial.println();
  
  Serial.print("Batch 3 End time : ");
  Serial.print(end_time_batch3.hour(), DEC);
  Serial.print(':');
  Serial.print(end_time_batch3.minute(), DEC);
  Serial.print(':');
  Serial.print(end_time_batch3.second(), DEC);
  Serial.println();

}

  }
vTaskDelay( 150/ portTICK_PERIOD_MS);

  }
}
void startTask4(void *parameter)
{
  
  while(1){
    if (batch_counter==1 && prod==10 )
{ 

digitalWrite(led_pin1 , HIGH);

}
if (batch_counter==2 && prod==20)
{

digitalWrite(led_pin2 , HIGH);

}
if (batch_counter==3 && prod==30)
{
digitalWrite(led_pin3 , HIGH);
batch_counter=0;
vTaskDelay( 100/ portTICK_PERIOD_MS);
digitalWrite(led_pin1 , LOW);
digitalWrite(led_pin2 , LOW);
digitalWrite(led_pin3 , LOW);
        vTaskSuspend(task_1);
        vTaskSuspend(task_2);
        vTaskSuspend(task_3);
}

  }
//vTaskDelay( 250/ portTICK_PERIOD_MS);

    
  }
void startTask5(void *parameter)
{
  
  while(1){     
  oled.print("Task 1 start time : ");
  oled.print(start_time_task1.hour(), DEC);
  oled.print(':');
  oled.print(start_time_task1.minute(), DEC);
  oled.print(':');
  oled.print(start_time_task1.second(), DEC);
  oled.println();
 vTaskDelay( 100/ portTICK_PERIOD_MS);
  oled.print("Task 1 End time : ");
  oled.print(end_time_task1.hour(), DEC);
  oled.print(':');
  oled.print(end_time_task1.minute(), DEC);
  oled.print(':');
  oled.print(end_time_task1.second(), DEC);
  oled.println();
  oled.display();

  oled.print("Task 2 start time : ");
  oled.print(start_time_task2.hour(), DEC);
  oled.print(':');
  oled.print(start_time_task2.minute(), DEC);
  oled.print(':');
  oled.print(start_time_task2.second(), DEC);
  oled.println();
 vTaskDelay( 100/ portTICK_PERIOD_MS);
  oled.print("Task 2 End time : ");
  oled.print(end_time_task2.hour(), DEC);
  oled.print(':');
  oled.print(end_time_task2.minute(), DEC);
  oled.print(':');
  oled.print(end_time_task2.second(), DEC);
  oled.println();
  oled.display();

  
  }
}

void startTask6(void *parameter){
  
 while(1){
  
oled.print("Task 3 start time : ");
  oled.print(start_time_task3.hour(), DEC);
  oled.print(':');
  oled.print(start_time_task3.minute(), DEC);
  oled.print(':');
  oled.print(start_time_task3.second(), DEC);
  oled.println();
 vTaskDelay( 100/ portTICK_PERIOD_MS);
  oled.print("Task 1 End time : ");
  oled.print(end_time_task3.hour(), DEC);
  oled.print(':');
  oled.print(end_time_task3.minute(), DEC);
  oled.print(':');
  oled.print(end_time_task3.second(), DEC);
  oled.println();
  oled.display();


  }

}
void setup() {
  Serial.begin(9600);
   Wire.begin(SDA_PIN_2 , SCL_PIN_2);
   if (!oled.begin(SSD1306_SWITCHCAPVCC,OLED_ADDR_1, SDA_PIN_1, SCL_PIN_1)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
}
delay(1000);
  oled.clearDisplay(); 

  oled.setTextSize(0.3);        
  oled.setTextColor(WHITE);   
  oled.setCursor(0, 1);       

  if (!oled2.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR_2, SDA_PIN_2, SCL_PIN_2)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
}
delay(1000);
 oled2.clearDisplay(); 

  oled2.setTextSize(0.3);        
  oled2.setTextColor(WHITE);   
  oled2.setCursor(0, 1);
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
  
  }
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);

    xTaskCreatePinnedToCore( startTask1,
                                "task 1",
                                2000,
                                NULL,
                                2,
                                &task_1,
                                app_cpu);

    xTaskCreatePinnedToCore( startTask2,
                              "task 2",
                              2000,
                              NULL,
                              2,
                              &task_2,
                              app_cpu);
    xTaskCreatePinnedToCore( startTask3,
                              "task 3",
                              2000,
                              NULL,
                              1,
                              &task_3,
                              app_cpu);
   xTaskCreatePinnedToCore(startTask4 ,
                              "Tunrn_on_Led's",
                              2000,
                              NULL,
                              1,
                              &task_4,
                              app_cpu);
  xTaskCreatePinnedToCore(startTask5 ,
                          "oled_display",
                          2000,
                          NULL,
                          1,
                          &task_5,
                          app_cpu);
  /*xTaskCreatePinnedToCore(startTask6 ,
          "oled_display2",
          2000,
          NULL,
          1,
          &task_6,
          app_cpu);*/
}
void loop() {
}
