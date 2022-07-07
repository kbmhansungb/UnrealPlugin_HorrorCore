// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HorrorItemInterface.h"
#include "HorrorInventoryComponent.generated.h"

class APlayerCameraManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSYSTEM_API UHorrorInventoryComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:	
	UHorrorInventoryComponent();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	APlayerCameraManager* CameraManager = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FHorrorItemStruct> Items;
};
