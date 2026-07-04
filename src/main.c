/**
 * @file main.c
 * @brief 鏈嶅姟鍣ㄤ富绋嬪簭鍏ュ彛 (瀵瑰簲 Go: main.go)
 */

#include "http_server.h"
#include "netif.h"
#include "ofono.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  const char *port = "6677";

  /* 瑙ｆ瀽鍛戒护琛屽弬鏁?*/
  if (argc > 1) {
    port = argv[1];
  }

  /* 瀹堟姢杩涚▼鍖?- 鍚庡彴杩愯鏃堕渶瑕?*/
  daemon(0, 0);

  /* 鍒囨崲鍒版湇鍔″櫒鐩綍浠ョ‘淇濈浉瀵硅矾寰勶紙闈欐€佹枃浠跺拰鏁版嵁搴擄級姝ｇ‘ */
  chdir("/home/root/6677");

  printf("=== ofono-server (C version) ===\n");

  /* 鍚屾绯荤粺鏃堕棿 */
  system("ntpdate ntp.aliyun.com > /dev/null 2>&1 &");

  /* 鍒濆鍖?ofono D-Bus 杩炴帴 */
  if (!ofono_init()) {
    fprintf(stderr, "璀﹀憡: ofono D-Bus 杩炴帴澶辫触锛岄儴鍒嗗姛鑳藉彲鑳戒笉鍙敤\n");
  }

  /* 鍒濆鍖栫綉缁滄帴鍙ｇ洃鍚紙鑷姩鎭㈠涔嬪墠鍚敤鐨勭洃鍚級 */
  init_netif();

  /* 鍚姩鏁版嵁杩炴帴鐩戝惉锛堟棤璁哄綋鍓嶇姸鎬侊級 */
  printf("鍚姩鏁版嵁杩炴帴鐩戝惉...\n");
  ofono_start_data_monitor();

  /* 鍚姩 HTTP 鏈嶅姟鍣?*/
  if (http_server_start(port) != 0) {
    fprintf(stderr, "鏈嶅姟鍣ㄥ惎鍔ㄥけ璐n");
    ofono_stop_data_monitor();
    ofono_deinit();
    return 1;
  }

  /* 杩愯浜嬩欢寰幆 */
  http_server_run();

  /* 娓呯悊 */
  http_server_stop();
  ofono_stop_data_monitor();
  ofono_deinit();

  return 0;
}
