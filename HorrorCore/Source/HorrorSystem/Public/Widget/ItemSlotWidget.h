// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.generated.h"

class UImage;
class IHorrorItemInterface;
class UItemListWidget;

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	UItemListWidget* ItemList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FIntPoint Index;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	float SquareSize = 90.f;

	UPROPERTY(BlueprintReadWrite, Meta = (BindWidget))
	UImage* Icon;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IHorrorItemActorInterface> GetItemInterface(bool& IsHold)  const;
	virtual TScriptInterface<IHorrorItemActorInterface> GetItemInterface_Implementation(bool& IsHold) const;


};
