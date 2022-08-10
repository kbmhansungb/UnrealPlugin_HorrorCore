# Horror Core

**Horror Core는 공포 게임에서 사용될 게임 시스템용 플러그인을 목표로 합니다.**

## 이름 및 폴더

**플러그인**
* 접두사로 Horror를 이용합니다.
* 접미사 Editor는 테스트와 같이, Editor에서만 존재해야 하는 코드 및 애셋이 존재합니다.

**CPP**

1. 플러그인또는 엔진 컨텐츠 단위로
2. Responsibility(책임) + Class(주요 부모 클래스)의 이름으로 정리합니다.

**블루프린트 폴더**

1. 플러그인또는 프로젝트의 컨텐츠 단위로
2. 1층으로 구성된, 
3. 클래스 타입으로 분류합니다.

* 블루프린트 클래스 상속은 애셋 확장으로 이용합니다.
* Category, ParentClass등 검색옵션으로 찾습니다.
* 목적또는 역활은 무엇이다에 비해 자주 변경됩니다.
* 따라서 상속 받은 하위 폴더별 구성은 이용하지 않습니다.
* 접미사를 이용하여 핵심적인 부모클래스로 분류합니다.
* 캐릭터의 애니메이션과 머티리얼은 접두사를 이용하여 분리합니다.
* 서로 강하게 결합되어 있고, 몇개 안되는 경우, 하위 폴더로 분류합니다.
* 클래스를 나타내므로 복수표현은 하지 않습니다.

**월드 아웃라이너**

1. 레벨로 분류합니다.
2. 보다 세부적인 분류가 필요한 경우 공간을 기준으로 폴더를 분류합니다. 

## 설치

에디터에 HorrorCore를 적용하는 방법은 Plugin 폴더에 (Git bash)서브모듈을 추가하여 사용합니다.

## More

각각의 내용에 대해서는 [Wiki](https://github.com/kbmhansungb/UnrealPlugin_HorrorCore/wiki)를 참고할 수 있습니다. 이 리포지토리는 플러그인이며 Overview를 담고있는 프로젝트는 [Unreal_HorrorCore](https://github.com/kbmhansungb/Unreal_HorrorCore)에서 확인 할 수 있습니다.
