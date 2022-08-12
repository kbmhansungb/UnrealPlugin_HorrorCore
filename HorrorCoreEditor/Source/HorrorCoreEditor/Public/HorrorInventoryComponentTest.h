// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <HorrorInventoryComponent.h>
#include <HorrorItemInterface.h>
#include <GameFramework/Actor.h>
#include <HorrorItemActorInterface.h>
#include "HorrorInventoryComponentTest.generated.h"

UCLASS()
class HORRORCOREEDITOR_API UTestInventoryComponent : public UHorrorInventoryComponent
{
	GENERATED_BODY()

public:
	UTestInventoryComponent();
};

UCLASS()
class HORRORCOREEDITOR_API ATestInventoryDelegateItemActor : public AActor,
	public IHorrorItemActorInterface
{
	GENERATED_BODY()

public:
	ATestInventoryDelegateItemActor();
	TScriptInterface<IHorrorItemInterface> ItemInterface;

	// IHorrorItemActorInterface에서 상속받음
public:
	virtual void GetItemInterface_Implementation(TScriptInterface<IHorrorItemInterface>& ItemInterface) override;
	virtual void HoldItemActor_Implementation(UHorrorHandComponent* HandComponent) override {}
	virtual void ReleaseItemActor_Implementation(UHorrorHandComponent* HandComponent) override {}
};

UCLASS()
class HORRORCOREEDITOR_API UTestInventoryDelegateItem : public UObject,
	public IHorrorItemInterface
{
	GENERATED_BODY()

	bool SaveResponse = false;
public:
	void Ready();

	UFUNCTION()
	bool IsDelegated() const;

	// IHorrorItemInterface에서 상속됨
public:
	virtual void GetItemName_Implementation(FName& ItemName) const;
	virtual int32 GetItemMaxStack_Implementation() const;
	virtual void GetItemActorClass_Implementation(TSubclassOf<AActor>& ItemActorClass) const;
	virtual void GetIconSize_Implementation(FIntSize2D& ItemIntSize) const;
	virtual void GetIconBrush_Implementation(FSlateBrush& ItemIcon) const;
};
