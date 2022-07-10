// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HorrorItemInterface.h"
#include "HorrorInventoryInterface.h"
#include "Widget_Inventory.h"
#include "HorrorInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSYSTEM_API UHorrorInventoryComponent : public UWidgetComponent
	, public IHorrorInventoryInterface
{
	GENERATED_BODY()

public:	
	UHorrorInventoryComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void InitWidget() override;

	virtual bool IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const override { return false; }
	virtual void StoreItem_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) override {}
	virtual bool IsTakable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const override { return false; }
	virtual TScriptInterface<IHorrorItemInterface> TakeItem_Implementation(FIntPoint Index) override { return TScriptInterface<IHorrorItemInterface>(); }
	virtual FIntSize2D GetInventorySize_Implementation() const override;

protected:
	UWidget_Inventory* InventoryWidget = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHorrorItemStruct> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FIntSize2D InventorySize;
};