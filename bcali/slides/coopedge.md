---
marp: true
paginate: true
theme: bcali

footer: Bcali B1 **kekeho**

---
<!--
class: title
-->

2022/2/28 Bcali 輪読

<br/>

# CoopEdge: A Decentralized Blockchain-based Platform for Cooperative Edge Computing

Liang Yuan, Qiang He, Siyu Tan, Bo Li, Jiangshan Yu, Feifei Chen, Hai Jin, and Yun Yang. 2020.
ACM Proceedings of the Web Conference 2021 (WWW '21)

<small>Link: [https://dl.acm.org/doi/abs/10.1145/3442381.3449994](https://dl.acm.org/doi/abs/10.1145/3442381.3449994)</small>

Bcali B1 **kekeho**

---
<!--
class: slides
-->

# Abstract

- Edge Computing (**EC**) が注目されている
  - 遠い雲の上にあるクラウドと違い, 端末の近くにサーバーを配置し, 低レイテンシで計算するやつ
- エッジサーバーの計算資源は限られているので, キャパを超えたら計算のオフロードをしたい
- 各エッジサーバーは異なるステークホルダーによって運営されている
  <small>(例: セルラーの基地局にエッジサーバーが置かれているケースだと, docomo, au, softbankなどが混在している)</small>
  - お互いを信頼できない
  - タスクを受け入れるインセンティブがない
  - オフロード先を(中央からのコントロールではなく)自律的に決定したい

---

# Abstract

- 協調的なECを推進するブロックチェーンベースの分散型プラットフォームである**CoopEdge**を提案している
- オフロードしたくなったら, 報酬を提示して複数の候補を募る
- "評判"に沿ってオフロード先のサーバーが選ばれる
- タスク実行のパフォーマンスがブロックチェーンに記録される
  - 記録された履歴は, 評判形成に活用される
- 信頼・インセンティブ付与に貢献
- Hyperledger SawtoothをベースにCoopEdgeを実装し, 性能を評価した
  →有用性があることが確認された

---

# Edge Computingとは

- 近年, モバイルデバイスの普及, IoTの流行, 自動運転車, WebXR, オンラインゲーム...
  - レイテンシに敏感なものが多い
- クラウドはエンドデバイスから遠いところにあるので, 大きなレイテンシが発生する
- エンドデバイスになるべく近い位置で計算ができると, レイテンシが小さくなってうれしい
- エッジサーバーをキャリアの基地局に置いたり, アクセスポイントに置いて, そこで計算をやってしまおうというパラダイム

![bg right:30% contain](https://upload.wikimedia.org/wikipedia/commons/b/bf/Edge_computing_infrastructure.png)

---

# 計算のオフロード

- キャリアの基地局や, アクセスポイントは小規模なので, クラウドのデータセンターみたいに無限に近いコンピュティングリソースを配置することは出来ない
- キャパを超えてきたら, 近隣のエッジサーバーに計算をオフロードしたい

![bg right contain](https://dl.acm.org/cms/attachment/f2683b4e-8efd-41b2-993a-0aab0718d59c/www21-209-fig1.jpg)

---

# 計算のオフロード

## 問題

- 近隣のエッジサーバーが, 同じ会社によって運営されているとは限らない
- 計算を依頼されたサーバーは, 競合他社のために真面目に素早く計算するモチベがない

- CoopEdgeでインセンティブを付与していい感じに協力させる

![bg right contain](https://dl.acm.org/cms/attachment/f2683b4e-8efd-41b2-993a-0aab0718d59c/www21-209-fig1.jpg)

---

# CoopEdgeの概要

## 登場人物

- Task Publisher
  計算タスクをオフロードしたいエッジサーバー
- Task Candidate
  計算タスクを実行する候補サーバー
- Task Executer
  計算タスクを実行するサーバー(1タスクあたり1つ)
- Task Recorder
  Task Executerの実行パフォーマンスを記録するエッジサーバー

---


# CoopEdgeの概要

## ステップ

1. 計算タスクをオフロードしたいエッジサーバーがTask Publisherとなり, タスクの要件と基本報酬をすべてのエッジサーバーに公開する
2. 公開されたタスクを受信したエッジサーバーは, 自身とTask Publisher間のネットワーク遅延を調べる. 遅延がしきい値以内であれば, Task Candidateになることができる
3. Task PublisherはTask Candidateたちの中から最も信頼できるものを選び, 選択する. 選択されたエッジサーバーがTask Executerとなる.
4. Task PublisherはタスクをTask Executerにオフロードする

---

# CoopEdgeの概要

## ステップ


5. Task Executerはタスクを実行し, 結果をTask Publisherに返し, タスクの完了をブロードキャストする
6. Task Publisherは完了したタスクに関する情報(実行時間とか)をトランザクションとしてまとめ, ブロードキャストする
7. エッジサーバーの評判に基づき, Task Recorderが選択され, Task Recorderがブロックを生成する
8. Task Recorderはブロックをブロードキャストし, 他のエッジサーバーが検証し, ブロックに投票する. コンセンサスが得られれば, チェーンに記録される

---

# CoopEdgeの概要

## ステップ

![contain](https://dl.acm.org/cms/attachment/ee003f32-df09-4a32-9f70-521b5d3f4904/www21-209-fig2.jpg)

---

# インセンティブメカニズム

## 各エッジサーバーがクレジットを得る方法

- Task Executerとして, 時間通りにタスクを完了し, 取引報酬($r = r_b+r_e$)を受け取る
  - 基本報酬$r_b$: Task Publisherが決める. 要求した時間内にタスクを完了させればもらえる
  - 追加報酬$r_e$: タスクが要求した時間より早く終わったらもらえる(なるべく頑張るインセンティブ)
- Task Recorderとして, ブロックチェーンに正常にトランザクションをコミットしたときに帳簿報酬を受け取る

---

# インセンティブメカニズム

## 各エッジサーバーがクレジットを得る方法

<div style="display: flex; justify-content: space-around;">

<div>

$r_b = \left\lbrace \begin{matrix} r_b', \delta_e \le \delta_m \\ \\ 0 , \delta _e \gt \delta_m \end{matrix}\right.$

</div>

<div>

$r_e = \left\lbrace \begin{matrix} \frac{\lambda \cdot \left(\delta _m - \delta_e\right)}{\delta _m}, \delta_e< \delta _m \\ \\ 0 , \delta_e \ge \delta _m \end{matrix}\right.$

</div>

</div>

$r_b'$: Task Publisherによって公告された基本報酬
$\lambda$: ベースライン追加報酬
$\delta_m$: Task Publisherによって公告された最大実行時間
$\delta_e$: Task Executerがタスクを完了するのにかかった時間


---

# 評判メカニズム

- 指数移動平均(EMA)を使う. 最近のトランザクションほど高いウェイトを置く.
- トランザクションあたりの評判は追加報酬$r_e$を用いる

$$rp_{s}^{n+1} = \left\lbrace \begin{matrix} 0 & n = 0 \\ \rho \cdot r_{e}^{n+1} + \left(1- \rho \right)\cdot rp_{s}^{n} & n > 0 \end{matrix}\right.$$

$rp_s^n$: 過去$n$回のトランザクションから得た評判, $\rho \ (0 \le \rho \le 1)$: トランザクションの重みが時間とともに減少する速度を調節するパラメータ

![bg right:40% contain](https://dl.acm.org/cms/attachment/3f3f3ba3-797b-4d43-8336-86441ca3f5fb/www21-209-fig3.jpg)

---

# Task Executerの選定

- ECなのだから, レイテンシが短いとうれしい
- レイテンシが短く, かつ評判が高いエッジサーバーにお頼みしたい

## 選定の方法

1. タスクが公開されたら, Task Candidateたちは我先にとTask Publisherに通知する
2. Task Candidateの評判とレイテンシをMin-Maxで正規化
3. スコアを計算
$$sc_i = w_1 \cdot rp^{\prime }_i + w_2 \cdot \delta ^{\prime }_i$$
$\delta_i'$: 正規化された応答時間, $rp_{i}'$: 正規化された評判, $w \ (w_1 + w_2 = 1)$: 重み

---

# コンセンサスメカニズム

- よくわかりませんでした(...)
- PBFTベースの**PoER**というのを考えたらしい

![contain](https://dl.acm.org/cms/attachment/7db5c2ed-26c2-4914-98ba-d506466c8863/www21-209-fig4.jpg)

---

# 感じたこと

- コンソーシアム型ブロックチェーンのよいユースケースなのでは

- 計算結果の正しさは考慮されていないような?
  - そこらへん気になる人は, ひとつ上のレイヤで勝手に解決してくれという感じ?
  - ここがクリアできれば, 誰でも野良ノードが参加できるパブリック型に発展できるのでは?
