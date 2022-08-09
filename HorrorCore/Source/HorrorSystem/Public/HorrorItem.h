// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HorrorItemInterface.h"
#include "HorrorItem.generated.h"

class AActor;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UHorrorItem : public UPrimaryDataAsset, 
	public IHorrorItemInterface
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1))
	int32 StackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1))
	FIntSize2D Size = FIntSize2D(1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush IconBrush;

	// IHorrorItemInterface에서 상속됨
public:
	virtual void GetItemName_Implementation(FName& ItemName) const override;
	virtual int32 GetItemMaxStack_Implementation() const override;
	virtual void GetItemActorClass_Implementation(TSubclassOf<AActor>& ItemActorClass) const override;
	virtual void GetIconSize_Implementation(FIntSize2D& ItemIntSize) const override;
	virtual void GetIconBrush_Implementation(FSlateBrush& ItemIcon) const override;
};