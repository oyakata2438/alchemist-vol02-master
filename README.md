# Alchemist Vol.2

[![wercker status](https://app.wercker.com/status/1b499348699bddecaf284f2b0e13c3c0/s/master "wercker status")](https://app.wercker.com/project/byKey/1b499348699bddecaf284f2b0e13c3c0)

## 概要説明

Alchemist Vol.1ならびにワンストップ！転職本お疲れ様でした。

次はAlchemist Vol.2だ！

### この本の最終目的

技術書典5に出展して、技術で金（かね）を錬成しましょう。

### 内容

* クロスレビュー
  * 仮想通貨
  * 取引所
* ラボ特集
  * ラボのこと
  * 今後待ち受ける不動産2020年問題
  * 秘密基地の作り方... etc
* ほか、なんでも記事

企画案とかあればSlackで言っていただければ！

## 執筆・配布スケジュール（逆算）

期日|内容
----|----
7/15|目次を書きましょう
7/31|第1締め切り（これを守れた著者にはご褒美があります）
8/15|第2締め切り。これ以後は編集モードに入ります
8/31|完全入稿
9/1|プロモーション開始
10/8|技術書典5
未定|打ち上げ

## アルケミ本の収益について

今回は、原稿料ではなくtokenを発行予定です。

  - 費用
    + 印刷費などの経費
    + 打ち上げ費用
  - 利益
    + 50%: ラボにそのままぶちこむ（機材の充実化などなど）
    + 50%: ポイントシステムの原資

※ラボ利用ができない著者へのお礼は、tokenをそのまま原稿料に変換して差し上げる形式にすることも考慮に入れます。

### ポイントシステム

* 原資: 技術書典5など、様々な場で行うマネタイズ
* ポイント: 原資を元に様々なサービスを受ける権利を数値化したもの
* token: 固定レートでポイントにいつでも変換可能な、数値化したもの

### 技術書典5貢献tokenの取得方法

  - 執筆（早期入稿）
  - 執筆
  - 執筆者・寄稿者の勧誘
  - プロモーション
  - その他、本への貢献

### ポイントの使い方

ポイントシステム原資から充填される

* ラボ
  - ラボ有料会員が、yukiさんに支払う会費
  - ラボメンが、ラボ飯に参加するときの費用
* 錬金術Meetup
  - 錬金術Meetupの参加費（減額の方がいい可能性）
* 誰でもOK
  - アルケミグッズをもらう
  - アルケミ関連の本をもらう
  - アルケミ・ラボのオンラインサービスで使う

## 筆者紹介兼あとがき

Contributorsに、自己紹介と、執筆者コメントを忘れずに入れてください。HPとか、ツイッターとか、GitIDとか、自由に入れてください。またこの企画に参加してくれた理由とか、今後の技術書クラスタに期待すること、自分の活動の振り返りでも、なんでもありです。5行～10行くらいでお願いします。

## 執筆にあたってのお願い

（1）早めに目次にコミットする（執筆者の皆様へのお願い）

## Re:VIEWの書き方

[Re:VIEWチートシート](https://gist.github.com/erukiti/c4e3189dda179a0f0b73299fb5787838) を作ってみたので、参考にしてみてください。

## CI

werckerを使っています。リポジトリが更新されると自動でPDFが出力されます。

* https://app.wercker.com/erukiti/alchemist-vol02/runs

## インストール

細かい準備(TeX入れたり)は[『技術書をかこう！』](https://github.com/TechBooster/C89-FirstStepReVIEW-v2)に準じます。

### Dockerを使う方法

Dockerを使うのが一番手軽です。

```sh
$ docker run --rm -v `pwd`:/work vvakame/review /bin/sh -c "cd /work/articles ; review-pdfmaker config.yml"
```

### Docker使わずビルド

```sh
cd articles ; review pdfmaker config.yml
```

### 権利

ベースには、[TechBooster/ReVIEW\-Template: TechBoosterで利用しているRe:VIEWのテンプレート（B5/A5/電子書籍）](https://github.com/TechBooster/ReVIEW-Template) を使っています。

  * 設定ファイル、テンプレートなど制作環境（techbooster-doujin.styなど）はMITライセンスです
    * 再配布などMITライセンスで定める範囲で権利者表記をおねがいします
