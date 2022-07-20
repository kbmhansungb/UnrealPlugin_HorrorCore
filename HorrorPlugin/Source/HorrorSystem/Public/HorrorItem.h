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
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = 1, UIMin = 1))
	int32 StackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FIntSize2D Size = FIntSize2D(1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FSlateBrush IconBrush;

	// IHorrorItemInterface에서 상속됨
public:
	virtual const FName& GetItemName() const override { return Name; }
	virtual int32 GetItemMaxStack() const override { return StackSize; }
	virtual const TSubclassOf<AActor>& GetItemActorClass() const override { return ActorClass; }
	virtual const FIntSize2D& GetIconSize() const override { return Size; }
	virtual const FSlateBrush& GetIconBrush() const override { return IconBrush; }
};