// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ItemWidget.generated.h"

class UImage;
class IHorrorInventoryInterface;
class IHorrorItemInterface;
class UWidget_Inventory;

/**
 * 
 */
UCLASS()
class HORRORSYSTEM_API UWidget_ItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	UWidget_Inventory* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FIntPoint Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	int32 Stack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float SquareSize = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true, AllowedClasses = "HorrorItemInterface"))
	TScriptInterface<IHorrorItemInterface> ItemInterface;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UImage* Icon;

protected:

};
