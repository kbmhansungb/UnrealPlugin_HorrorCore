// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <HorrorSystem/Public/HorrorHoldableInterface.h>
#include "HorrorHoldableActor.generated.h"

class UActorSequenceComponent;

UCLASS()
class HORRORSYSTEM_API AHorrorHoldableActor : public AActor,
	public IHorrorHoldableInterface
{
	GENERATED_BODY()
	
public:	
	AHorrorHoldableActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(Category = "Horror|Holdable", VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMeshComponent;

	UPROPERTY(Category = "Horror|Holdable", VisibleAnywhere, BlueprintReadOnly)
	UActorSequenceComponent* PutSequence;

	// IHorrorHoldableInterface을(를) 통해 상속됨
public:
	virtual AActor* GetHoldableActor_Implementation() const override;
	virtual bool IsHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) const override;
	virtual void ResponseHoldHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) override;
	virtual void SetHoldableTransform_Implementation(const FTransform& DesireTransform) override;
	virtual void LerpHoldableTransform_Implementation(const FTransform& DesireTransform) override;
	virtual void ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) override;

};
