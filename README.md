방어적 프로그래밍 기준 필요.

# UnrealPlugin_HorrorCore
Developed with Unreal Engine

공포게임에서 사용하는 이벤트를 생성하고 관리하기 위한 목적으로 생성한 플러그인 입니다.

구현은 주어(Actor) 동사 목적어(Actor)의 가장 기본적인 문장을 바탕으로 하고 있습니다. 
여기서 목적어는 하나의 동사만을 허용하도록 작성했습니다. 따라서 동사는 생략됩니다.

```
그가 문을 열었다.
```

호러 이벤트는 이러한 문장구조 위해 발생하는 이벤트를 정의합니다.
아래의 예시에서 그가 문을 열었다. 다음이 정의되는 호러 이벤트 입니다.

```
그가 문을 열었다. 조명이 꺼지고 문이 닫혔다. 그리고 알수 없는 소리가 들린다.
```

## 주요 컨셉
* FHorrorEventRequired
* UHorrorEventInstance
* UHorrorEventComponent
* UHorrorEventCallerComponent

## 모듈 구성
* HorrorCore
	- 호러 이벤트를 실행하기 위한 내용이 정의되어 있습니다.
* HorrorEvent
	- 사용할 수 있는 HorrorEventInstance들이 정의되어 있습니다.
* 플러그인 컨텐츠
	- 샘플 에셋이 있습니다.

# 사용법
## 호러 이벤트 호출 설정
1. 호출할 수 있도록 세팅합니다.
	- HorrorEventCallerComponent를 플레이어 캐릭터에 생성합니다.
		- 이벤트를 Multicast하기 위해서 필요합니다.
	- HorrorEventComponent를 호러 이벤트를 발생시킬 액터에 생성합니다.
2. HorrorEventComponent에서 이벤트를 정의합니다.
	- 원하는 이벤트를 발생시키기 위해서 HorrorEventInstance를 인스턴스화 합니다.
	- HorrorEventInstance에 조건이 필요한 경우 EventCondition에 인스턴스를 추가합니다.
3. 클라이언트의 입력에서 HorrorEventCallerComponent를 이용하여 이벤트를 호출하는 로직을 작성합니다.

## 호러 아이템을 다른 아이템 시스템과 합치는 방법
다른 아이템 시스템, 예로 아이템 애셋 클래스에 호러 아이템인터페이스를 구현하여 사용할 수 있습니다.