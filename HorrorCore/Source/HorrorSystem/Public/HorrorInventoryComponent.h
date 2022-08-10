// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HorrorItemInterface.h"
#include "HorrorInventoryInterface.h"
#include "Widget/InventoryWidget.h"
#include "Horror2DInventoryStruct.h"
#include "HorrorInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSYSTEM_API UHorrorInventoryComponent : public UWidgetComponent, 
	public IHorrorInventoryInterface
{
	GENERATED_BODY()

public:	
	UHorrorInventoryComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHorror2DInventoryStruct Inventory;
	
public:
	UPROPERTY(BlueprintAssignable)
	FInventoryChangedDelegate InventoryChangedDelegate;

public:
	virtual void InitWidget() override;

	// IHorrorInventoryInterface에서 상속함
public:
	virtual bool IsStorable_Implementation(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const override;
	virtual bool StoreItem_Implementation(const TScriptInterface<IHorrorItemActorInterface>& ItemActor, FIntPoint Index) override;
	virtual bool IsTakable_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const override;
	virtual bool TakeItem_Implementation(FIntPoint Index, TScriptInterface<IHorrorItemActorInterface>& ItemActor) override;
	virtual void GetInventorySize_Implementation(FIntSize2D& InventorySize) const override;
	
protected:
	UInventoryWidget* InventoryWidget = nullptr;
};