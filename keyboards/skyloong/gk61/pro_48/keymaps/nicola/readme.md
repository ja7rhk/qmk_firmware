# SKYLOONG GK61 Pro 向け Nicola配列キーマップ

キーボード側で親指シフトをローマ字(※英字キー入力から仮名への変換方式)出力するためのキーマップです。  
物理的なキー配置はANSI配列で、Windowsの設定では日本語/英語キーボード(101/102キー)配列で使用します。  
「」や『』・などは直接出力できませんから、MS-IMEなどの変換機能で確定します。

## 配列
![Layout](assets/gk61_pro_nicola_layout.png "Layout")

## Nicola のオンとオフ
本キーボードはF14でMS-IME側"IME on"、CAPSLOCKで"IME off"に切り替えることを想定しています。  
hoboNicolaで使用している"observe_ime"はIMEの状態からキーボードにNum Lockで返します。  
キーボードではNum Lockの状態でNicolaモードを切り換えます。  
こうすることで、Windowsのアプリ毎のIME状態がキーボードに反映されるので、いわゆるモードずれを気にする必要がありません。  
※この機能を利用しない場合はkeymap.cの#define USE_OBSERVE_IMEをコメントアウトして下さい。  

## 情報元
* https://github.com/sadaoikebe/qmk_firmware/ をベースにNicolaを実装しています。 
* https://github.com/okiraku-camera/observe_ime hoboNicolaで使用しているobserve_imeの情報です。
