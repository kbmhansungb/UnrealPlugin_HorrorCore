// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "HorrorHoldableInterface.h"
#include "HorrorHandComponent.h"
#include "HorrorHandComponentTest.generated.h"

UCLASS()
class HORRORCOREEDITOR_API UTestHorrorHoldableObject : public UObject,
	public IHorrorHoldableInterface
{
	GENERATED_BODY()

public:
	virtual void ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface);
};


UCLASS()
class HORRORCOREEDITOR_API UTestHorrorHoldableHoldReleaseTestObject : public UObject,
	public IHorrorHoldableInterface
{
	GENERATED_BODY()

public:
	bool IsReleased = false;

	virtual void ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface);
};