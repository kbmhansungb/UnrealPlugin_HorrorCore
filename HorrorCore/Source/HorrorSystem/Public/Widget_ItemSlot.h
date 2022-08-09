// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_ItemSlot.generated.h"

class UImage;
class IHorrorItemInterface;
class UWidget_ItemList;

/**
 * 
 */
UCLASS(Abstract)
class HORRORSYSTEM_API UWidget_ItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	UWidget_ItemList* ItemList;

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
