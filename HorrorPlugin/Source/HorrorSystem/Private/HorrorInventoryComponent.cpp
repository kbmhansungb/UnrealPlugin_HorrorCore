// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorInventoryComponent.h"
#include <Kismet/GameplayStatics.h>

UHorrorInventoryComponent::UHorrorInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Space = EWidgetSpace::World;
}

void UHorrorInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHorrorInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHorrorInventoryComponent::InitWidget()
{
	Super::InitWidget();

	InventoryWidget = Cast<UWidget_Inventory>(GetWidget());
	InventoryWidget->Inventory = this;
}

FIntSize2D UHorrorInventoryComponent::GetInventorySize_Implementation() const { return InventorySize; }

