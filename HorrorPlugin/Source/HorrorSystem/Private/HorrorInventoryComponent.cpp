// 2022 06    Bum moo, Kim    Free copyright


#include "HorrorInventoryComponent.h"
#include <Kismet/GameplayStatics.h>

UHorrorInventoryComponent::UHorrorInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Space = EWidgetSpace::World;
}


// Called when the game starts
void UHorrorInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UHorrorInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CameraManager == nullptr)
	{
		CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	}
}

