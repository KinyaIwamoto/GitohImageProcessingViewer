# GitohImageProcessingViewer
GitohImageProcessingViewer(GIPV)はカメラ入力、動画ファイル、静止画ファイルで画像処理を行うためのテンプレートアプリケーションです。</br>
このプログラムをビルドしただけでは単に画像の表示しかしません。ソースコード内に画像処理コードを記述することでその処理結果をカメラ入力、動画ファイル、静止画ファイルで確認することが出来ます。</br>
Win32APIとMFCの2種類のプロジェクトを準備しています。シンプルに画像処理を確認したい場合はWin32APIプロジェクトを使用し、ダイアログボックスを使用して各種設定を切り替える処理を記述したい場合はMFCプロジェクトを使用することを推奨します。</br>
GIPVを構築するにあたり、I.N.氏（http://insubaru.g1.xrea.com/）のEWCLIB、ESPLIB、EVFLIBという3ライブラリを使用させていただいてます。非常に優れたライブラリを提供していただきありがとうございます。</br>

GitohImageProcessingViewer (GIPV) is a template application for image processing with camera input, video files, and still image files.</br>
If you just build this program, it will only display the images. By writing the image processing code in the source code, you can check the result of the processing on the camera input, video file, and still image file.</br>
We have prepared two types of projects, Win32API and MFC. We recommend using the Win32API project if you want to simply check the image processing, and using the MFC project if you want to describe the process of switching various settings using dialog boxes.</br>
We are using three libraries, EWCLIB, ESPLIB and EVFLIB by I.N. (http://insubaru.g1.xrea.com/) to build GIPV. Thank you very much for providing such excellent libraries.</br>