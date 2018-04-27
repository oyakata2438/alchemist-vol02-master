# Alchemist Vol.2

[![wercker status](https://app.wercker.com/status/1b499348699bddecaf284f2b0e13c3c0/s/master "wercker status")](https://app.wercker.com/project/byKey/1b499348699bddecaf284f2b0e13c3c0)

## 概要説明

技術書典4ならびにAlchemist Vol.1、お疲れ様でした。さぁVol.2だ

## この本の最終目的

夏コミに出展して、技術を錬金しましょう。

## 執筆・配布スケジュール（逆算）

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
