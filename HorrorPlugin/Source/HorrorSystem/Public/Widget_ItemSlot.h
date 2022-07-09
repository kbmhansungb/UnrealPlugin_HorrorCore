// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ItemSlot.generated.h"

class UImage;
class IHorrorInventoryInterface;

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UWidget_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	TScriptInterface<IHorrorInventoryInterface> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FIntPoint Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float SquareSize = 90.f;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UImage* Icon;
};
