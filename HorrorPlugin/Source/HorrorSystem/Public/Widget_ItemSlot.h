// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ItemSlot.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UWidget_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntPoint Index;
};
