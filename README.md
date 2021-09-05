# QT/Android Foreground Service
## An Endless service with a QT process

Originally I created this project for work and I would not advise you to use QT in an Android service unless if you absolutely have to. You have been warned. 

## Features

- Runs endlessly, bypassing doze mode. More on why this is a thing [here][doze]
- No power or permission restrictions as long as you start from provided app (or an app running on foreground). Why this is needed [here][restriction]
- Comes with UDP based inter-application communication classes since it cannot be debugged as an application. See "Known Issues"
- Comes with another foreground service app bundle which retrives GNSS information without Google services and sends them to QT service. See "Known Issues"

## Known Issues

- Android sevices of any kind cannot be bound to debugger. This is a known bug in QT and is not resolved since 2016 so dont hold your breath. See bug entry [here][bug entry]. Implication is you cannot use debug console to debug your service (app itself still works) so prints/qDebug won't show in your console as well as exceptions/errors. Hence the UDP logger
- QT Location libraries does not work with service process (reason unknown to me)
- Any QT library depending on UI elements bound to cause problems since Android services are not permitted any user interface apart from notifications
- On some Windows host machines this fails to deploy due to Windows path length limitations depending on where you store your JDK and Android SDK's. Try moving them and your project to shorter paths. Also there is some regedit magic to remove path limitation [here][pathlength], altough it is not tested (HMU if you solved a deploy problem with this)
- Actual log file creation may fail on Android 10 and up

## Installation
- This should work with any QT or Android version so far but here is my versions of things:

| Package/lib | Version |
| ------ | ------ |
| QT | 5.14.2 |
| JDK | 1.8.0_251 |
| NDK | 21.1.6352462 |
| ABI | armeabi v7a |

- Use service.pro file to open the project and you should be good to go


## License

MIT

   [doze]: <https://developer.android.com/topic/performance/power>
   [restriction]: <https://developer.android.com/guide/components/foreground-services#bg-access-restrictions>
   [bug entry]: <https://bugreports.qt.io/browse/QTCREATORBUG-16886t>
   [pathlength]: <https://www.howtogeek.com/266621/how-to-make-windows-10-accept-file-paths-over-260-characters/>
  
