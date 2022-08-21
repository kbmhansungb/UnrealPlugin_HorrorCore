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

	// IHorrorHoldableInterface을(를) 통해 상속됨
	virtual AActor* GetHoldableActor_Implementation() const override;
	virtual bool IsHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) const override;
	virtual void ResponseHoldHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) override;
	virtual void SetHoldableTransform_Implementation(const FTransform& DesireTransform) override;
	virtual void LerpHoldableTransform_Implementation(const FTransform& DesireTransform) override;
};


UCLASS()
class HORRORCOREEDITOR_API UTestHorrorHoldableHoldReleaseTestObject : public UObject,
	public IHorrorHoldableInterface
{
	GENERATED_BODY()

public:
	bool IsReleased = false;

	virtual void ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface);

	// IHorrorHoldableInterface을(를) 통해 상속됨
	virtual AActor* GetHoldableActor_Implementation() const override;
	virtual bool IsHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) const override;
	virtual void ResponseHoldHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) override;
	virtual void SetHoldableTransform_Implementation(const FTransform& DesireTransform) override;
	virtual void LerpHoldableTransform_Implementation(const FTransform& DesireTransform) override;
};