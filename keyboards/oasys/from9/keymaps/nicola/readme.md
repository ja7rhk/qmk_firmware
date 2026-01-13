# OASYS [FROM9] 用 Nicola配列キーマップ
キーボード側で親指シフトをローマ字(※英字キー入力から仮名への変換方式)出力するためのキーマップです。  
物理的なキー配置はワープロ専用機OASYS配列で、Windowsの設定では日本語/日本語キーボード(109キー)配列で使用します。  
「」や『』・などは直接出力できませんから、MS-IMEなどの変換機能で確定します。

* 左親指キー : 単押し → (無変換キー) 、長押し → TAB(変換候補)
* 右親指キー : 単押し → (変換キー)

## 配列
![](oasys_lite_from9.png)

※FNキーで有効になります。

![](oasys_lite_from9_fn.png)

## Nicolaモードの制御
本キーボードはhoboNicolaで使用している"observe_ime"を使うことを想定しています。 
Windowsのアプリ毎のIME状態がキーボードに反映されるので、いわゆるモードずれを気にする必要がありません。   

(1) 左親指キーでMS-IME側"IME on"、CAPSLOCKで"IME off"に切り替える。  
(2) "observe_ime"はIMEの状態からキーボードにNum Lockで通知する。  
(3) キーボードではNum Lockの状態に従ってNicolaモードをon/offする。  

※この機能を利用しない場合は\ossys\from9\config.hの#define USE_OBSERVE_IMEをコメントアウトして下さい。  

## 制限事項
* Nicolaモードのとき、キーのリピートは効きません。
* SHIFTキーを押しながらの英字入力はできません。

## 情報元
* https://github.com/sadaoikebe/qmk_firmware/ をベースにNicolaを実装しています。 
* https://github.com/okiraku-camera/observe_ime hoboNicolaで使用しているobserve_imeの情報です。
