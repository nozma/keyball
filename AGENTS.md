# AGENTS ガイド

このリポジトリには複数レイアウトのキーボード向けファームウェアが含まれていますが、運用対象は Keyball44 と Keyball39 です。他のディレクトリは原則参照不要です。また、keyball44/doc/ディレクトリも参照不要です。ただし、トラックボールのファームウェアを修正したい場合などはdriversディレクトリも参照してください。

## 基本方針
- Keyball44 / Keyball39 用ファームウェアと関連ドキュメントだけを更新対象にする。
- QMK ベースの構成であることを前提に、`qmk_firmware` への反映やビルドに影響しないか確認する。
- 運用は Vial 対応ファームウェアのみを前提とする。Vial で正しく認識・操作できることを優先して確認する。

## 主要ディレクトリとファイル
- `qmk_firmware/` : QMK のサブモジュール。Keyball44 / Keyball39 配下と drivers のみ編集対象。

## .qmk_work の準備
- `.qmk_work/` はビルド用の独立した QMK ツリー。最初に作業する際はリポジトリ直下で `git clone --depth=1 https://github.com/qmk/qmk_firmware.git .qmk_work` を実行して用意する。
- 依存ツールは QMK 公式手順に沿ってインストールする。`python3 -m pip install -r requirements.txt`（または `qmk setup`）を `.qmk_work` 内で実行しておくとビルドが通りやすい。
- `.qmk_work` は Git 管理対象外なので、必要に応じて同期や再構築を手動で行う。

## 作業フローの目安
1. 変更は `keyball44` / `keyball39` 配下に閉じ、他機種のレイアウトやキーマップを巻き込まないようにする。
2. ビルドやテストが必要な場合は、QMK ツールチェーンを使用して対象キーボード（`keyball44` または `keyball39`）のみをビルドする。
3. 変更後は Vial での動作（認識・キーマップ編集・トラックボール制御など）を確認する。

## 注意点
- ドキュメントファイルは原則更新不要。
- 他モデル（`keyball46`, `keyball61` など）は無視してよい。誤って変更しないようブランチ運用で隔離する。
- 英語資料が混在するが、ユーザー向け最終成果は日本語でまとめる。
- トラックボール関連の設定を変更する場合、`test` ビルドでハードウェア検証を行ってから Vial 用ファームウェアに反映する。
- `qmk_firmware/` 直下に `builddefs/` や `drivers/` などのフル QMK ソースを展開しない。生成されてしまった場合でも `.gitignore` 済みなのでコミットしない。

## ビルドメモ
- 実際のビルドは `.qmk_work/` 以下の QMK ツリーで行う。
- `qmk_firmware/` 側でファイルを編集したら、ビルド前に必ず同期する。
  1. 同期対象が単体ファイルの場合は `rsync -a qmk_firmware/<path>/ keymap destination` を用いる（例：`rsync -a qmk_firmware/keyboards/keyball/keyball44/keymaps/vial/ .qmk_work/keyboards/keyball/keyball44/keymaps/vial/`）。
  2. 複数ファイルをまとめて更新した場合も同様にディレクトリ単位で同期し、`.qmk_work` 側を最新化してからビルドする。
- ビルドコマンドは `.qmk_work` ディレクトリで `make keyball/keyball44:vial` または `make keyball/keyball39:vial` を使用する。`qmk compile` は設定が噛み合わず失敗するため現状は非推奨。
- ビルド中に `keyboard.json` などに関する警告が出るが、Keyball 用カスタム構成では既知であり無視してよい。
- 生成物は `.qmk_work/.build/keyball_keyball44_vial.uf2` や `.qmk_work/.build/keyball_keyball39_vial.uf2` に出力される。必要に応じてコピーして実機へ書き込む。
