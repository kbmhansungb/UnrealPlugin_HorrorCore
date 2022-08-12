// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UImage;
class IHorrorInventoryInterface;
class IHorrorItemInterface;
class UInventoryWidget;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	UInventoryWidget* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FIntPoint Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float SquareSize = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowedClasses = "HorrorItemInterface"))
	TScriptInterface<IHorrorItemInterface> ItemInterface;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UImage* Icon;

protected:

};
