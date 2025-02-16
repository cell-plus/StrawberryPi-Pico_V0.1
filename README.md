# StrawberryPi-Pico
土壌水分センサー・ポンプ・LEDを搭載した植物栽培特化型デバイス「StrawberryPi-Pico」

======V0.1.0-202501=========

・回路図　：https://image-pro.easyeda.com/pullimages/08d8bb2dcfd34de89ee88f67925cd60f.webp

・PCB図面　：https://image-pro.easyeda.com/pullimages/37ff79a8831c460f9f59f0e0ebcc0b90.webp

※NPNトランジスタの電流容量が足りていないのでポンプが正常に動作しない不具合あり。

=========================

======V0.1.1-202501=========

・変更点：NPNトランジスタの代わりにNchMOSFETに変更

　　　　-部品レイアウト、回路パターンの見直し

・回路図　：https://image-pro.easyeda.com/pullimages/562a710350c64bd2afdc438bb16337d1.webp

・PCB図面　：https://image-pro.easyeda.com/pullimages/f3d689709e2e455f8fa6b473361468a3.webp

========================

 

免責 

本器は自己責任において利用するものとし、利用者が被った不利益または損害について一切責任を負いません。 

本書の情報は2025年1月現在のものです。記載されたURLや手順が変更になる場合があります。 

　

注意事項 

●供給電源　：	定格電圧5VDC　消費電流未計測　(USB電源) 

●設定環境　：	USB接続、Arduino IDEでの書き込みが出来るPC環境をご準備ください。 

●設置環境　：			・塵埃、金属粉、水滴飛散などの多いところでは防塵設計の筐体に収納してください。 

・温度が60℃を越える環境、結露する環境では使用しないでください。 

●その他　　：	本器は電源投入と同時に動作開始します。 



 機能内容(サンプルプログラム) 

●土壌水分センサーによる、土の湿り具合のセンシング。 

●センサー値に応じてLED(本器基板上およびLEDテープ)の色を変更。(赤→黄→緑→青)  

●センサー値が閾値以下のとき、ポンプが設定時間動作。  

●ポンプ動作中は本器基板上のLEDが白色にも点滅。  

　

キット付属品と配線接続 

　●ウォーターポンプ　：	https://amzn.asia/d/5MyBmeY 

　　デュポンコネクタなどで配線加工してください。(メス,二つ口)　参考：https://amzn.asia/d/89GqBZK 

　接続：Pump　VSS：赤線、　VCC：黒線 

　●静電容量式土壌水分センサー　：	https://amzn.asia/d/6kMGpRw 

　　接続：Sensor　A0：黄線、　3V3：赤線、　GND：黒線 

 

オプション:キットに含まれません。なくても動作します。 

　●NeoPixel LEDテープ(144連)　：	https://amzn.asia/d/j20iAux	 

　　接続：LED　GND：白線、　25：緑線、　VSS：赤線 

　 

 　

初期設定 

・StrawberryPi-PicoにUSBケーブルを接続。 

・StrawberryPi-Pico のBOOTボタンを押しながら、USBケーブルをPCに接続。 

・PCでは StrawberryPi-Pico をストレージとして認識。 

・下記URLからUF2ファイルをダウンロードして、ストレージに保存。 

　　　https://circuitpython.org/board/raspberry_pi_pico/ 

・Arduino IDEの環境設定。(Arduino IDEの導入方法は割愛。) 

　・ボードライブラリの追加。 

　　IDE：ファイル>基本設定>追加のボードマネージャのURLに、 

( https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json )　を入力し適用。 

　　IDE：ボードマネージャ>「RP2040」で検索>「Raspberry Pi Pico/RP2040/RP2350　by Earle F. Philhower」　をインストール。 

・ボードの選択。 

　IDE：ツール>ボード>Raspberry Pi Pico/RP2040/RP2350>Waveshare RP2040 Zero 

　　　を選択。 

・環境設定完了。Arduino IDEでプログラム書き込み可能。 

　

サンプルプログラム 

https://github.com/cell-plus/StrawberryPi-Pico/blob/main/main.ino 

動作内容：	センサー値に応じてLEDの色を変更。(赤→黄→緑→青) 

センサー値が閾値以下のとき、ポンプが設定時間動作。 

ポンプ動作中はStrawberryPi-Pico基板上のNeoPixelが白色にも点滅。 

※各閾値はご利用の環境に応じて調整してください。 

　

その他 

下記のピンを使用することが出来ます。温湿度センサーなどの機能拡張にご利用ください。 

拡張ピン：0、1、14、15、27/A1、28/A2、29/A3	電源ピン：3V3、VSYS/5V、GND 



 
