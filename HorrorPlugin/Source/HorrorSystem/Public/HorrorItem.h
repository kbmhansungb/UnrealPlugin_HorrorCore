// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HorrorItemInterface.h"
#include "HorrorItem.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UHorrorItem : public UPrimaryDataAsset
	, public IHorrorItemInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 StackSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* Actor;

private:
	virtual FName GetItemName_Implementation() override;
	virtual int32 GetItemMaxStack_Implementation() override;
	virtual AActor* GetItemActor_Implementation() override;
};