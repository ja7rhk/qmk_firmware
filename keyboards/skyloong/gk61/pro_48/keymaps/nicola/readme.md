# [SKYLOONG GK61 Pro](https://skyloongtech.com/skyloong-gk61pro/ref/13/) 向け Nicola配列キーマップ
キーボード側で親指シフトをローマ字(※英字キー入力から仮名への変換方式)出力するためのキーマップです。  
物理的なキー配置はANSI配列で、Windowsの設定では日本語/英語キーボード(101/102キー)配列で使用します。  
「」や『』・などは直接出力できませんから、MS-IMEなどの変換機能で確定します。

* 左親指キー : 単押し → F14(無変換キー) 、長押し → TAB(変換候補)
* 右親指キー : 単押し → Spaceキー 、長押し → F15(変換キー)

## 配列
![Layout](assets/gk61_pro_nicola_layout.png "Layout")

※右下の修飾キーはFNキーで有効になります。通常はカーソル移動に使用します。

## Nicolaモードの制御
本キーボードはhoboNicolaで使用している"observe_ime"を使うことを想定しています。 
Windowsのアプリ毎のIME状態がキーボードに反映されるので、いわゆるモードずれを気にする必要がありません。   

(1) F14でMS-IME側"IME on"、CAPSLOCKで"IME off"に切り替える。  
(2) "observe_ime"はIMEの状態からキーボードにNum Lockで通知する。  
(3) キーボードではNum Lockの状態に従ってNicolaモードをon/offする。  

※この機能を利用しない場合は\pro_48\config,hの#define USE_OBSERVE_IMEをコメントアウトして下さい。  

## 制限事項
* Nicolaモードのとき、キーのリピートは効きません。
* SHIFTキーを押しながらの英字入力はできません。

## observe_imeとMS-IMEの設定

アダプターを使用する場合、observe_imeを利用すると所謂モードずれがないので便利です。GK61 proは10キーがないのでNumLockでモード切替えをします。

![](assets/observe_ime_num.png)

USキーボードは無変換・変換キーがないのでF14/F15を使用します。以下はMS-IMEの設定例です(以前のバージョンを使用)。カナ変換はF7キーで出来ます。

![](assets/ms_ime.png)

## 情報元
* https://github.com/sadaoikebe/qmk_firmware/ をベースにNicolaを実装しています。 
* https://github.com/okiraku-camera/observe_ime hoboNicolaで使用しているobserve_imeの情報です。
