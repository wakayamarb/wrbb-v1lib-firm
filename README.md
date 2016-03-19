# wrbb-v1lib-firm
Wakayama.rb Ruby Board V1 library Firmware

　Wakayama.rb のV1ライブラリを使ったRubyボードのソースです。
　V1ライブラリとは、特殊電子回路株式会社さんの無償版FreeRXduinoライブラリを示します。

  バージョンのARIDAやUmeJamの後の数字は基板番号を表します。
  バージョン最後のf2やf3はバイトコードフォーマットの番号です。mruby1.0.0ベースの場合はf2となります。

  mruby ver1.0.0 -> ByteCode Format Ver.0002
  mruby ver1.1.0 -> ByteCode Format Ver.0003
  mruby ver1.2.0 -> ByteCode Format Ver.0003
    
WAKAYAMA.RB Board Ver.ARIDA5-1.52(2016/3/19)f3(256KB), mruby 1.2.0
                        |      |      |      |   |
                        |      |      |      |   |
                        |      |      |      |  RAM Size
                        |      |      |      |
                        |      |      |   ByteCode Format Number
                        |      |      |
                        |      |    作成日
                        |      |
                        | Firmware Version
                        |
                   回路基板番号
    



------
  It is a source of mruby board of Wakayama.rb.

--
##How to use Wakayama.rb board
http://www.slideshare.net/MinaoYamamoto/wakayamarb-arida-4
--
##Link
[特殊電子回路株式会社さんの無償版FreeRXduinoライブラリ](http://rx.tokudenkairo.co.jp/freesoft.html)

--
##License
 Wakayama.rb-Ruby-Board-V1-library-Firmware is released under the [MIT License](MITL).
