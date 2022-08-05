// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorHandInterface.h"
#include "HorrorHandComponent.generated.h"

UENUM(BlueprintType)
enum EHandType
{
	RIGHT,
	LEFT,
};

USTRUCT(BlueprintType)
struct HORRORSYSTEM_API FHoldStruct
{
	GENERATED_BODY()

public:
	FHoldStruct() {}
	FHoldStruct(const FVector& RelativePosition) : RelativePosition(RelativePosition) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IHorrorHoldableInterface> HoldItem;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HORRORSYSTEM_API UHorrorHandComponent : public USceneComponent, 
	public IHorrorHandInterface
{
	GENERATED_BODY()

public:	
	UHorrorHandComponent();
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual bool IsDominanceHand_Implementation() const override;
	virtual TScriptInterface<IHorrorHoldableInterface> GetHoldable_Implementation() const override;
	
public:
	UFUNCTION(BlueprintCallable)
	bool IsEmptyHand(const EHandType Type);

	UFUNCTION(BlueprintCallable)
	void Hold(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable);

	UFUNCTION(BlueprintCallable)
	void Swap();

	UFUNCTION(BlueprintCallable)
	void Release(const EHandType Type);

public:
	void Lerp(float Deleta);
	void SetStart(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable);
	
	const FHoldStruct* GetHoldStruct(const EHandType Type) const;
	FHoldStruct* GetHoldStruct(const EHandType Type);

	const FHoldStruct& GetRightStruct() const;
	const FHoldStruct& GetLeftStruct() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EHandType> HandDominance = EHandType::RIGHT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct RightHand = FHoldStruct(FVector(0.f, 20.f, 0.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct LeftHand = FHoldStruct(FVector(0.f, -20.f, 0.f));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartOffset = FVector(0.f, 0.f, -30.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpSpeed = 5.0f;
};

