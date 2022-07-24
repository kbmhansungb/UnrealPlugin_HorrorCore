// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HorrorItemInterface.h"
#include "HorrorInventoryInterface.h"
#include "Widget_Inventory.h"
#include "Horror2DInventoryStruct.h"
#include "HorrorInventoryComponent.generated.h"

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
	virtual void InitWidget() override;

	// IHorrorInventoryInterface에서 상속함
public:
	virtual bool IsStorable(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) const override;
	virtual bool StoreItem(const TScriptInterface<IHorrorItemInterface>& Iteminterface, FIntPoint Index) override;
	virtual bool IsTakable(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) const override;
	virtual bool TakeItem(FIntPoint Index, TScriptInterface<IHorrorItemInterface>& Iteminterface) override;
	virtual const FIntSize2D& GetInventorySize() const override;;
	
protected:
	UWidget_Inventory* InventoryWidget = nullptr;
};