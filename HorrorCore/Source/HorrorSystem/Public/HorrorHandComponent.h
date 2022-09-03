// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HorrorHandInterface.h"
#include "HorrorHandComponent.generated.h"

UENUM(BlueprintType)
enum class EHandType : uint8
{
	// None,
	RIGHT,
	LEFT,
};

USTRUCT(BlueprintType)
struct HORRORSYSTEM_API FHoldStruct
{
	GENERATED_BODY()

public:
	FHoldStruct() = default;
	FHoldStruct(const FVector& RelativePosition) : RelativePosition(RelativePosition) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector RelativePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TScriptInterface<IHorrorHoldableInterface> HoldingItem;

public:
	bool IsEmpty() const;
	bool IsHoldingItem(const TScriptInterface<IHorrorHoldableInterface>& Other) const;

	void HoldItem(const TScriptInterface<IHorrorHoldableInterface>& NewHoldingItem, const TScriptInterface<IHorrorHandInterface>& HandInterface);
	void ReleaseHoldingItem(const TScriptInterface<IHorrorHandInterface>& HandInterface);
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

	// IHorrorHandInterface에서 상속됨
public:
	virtual void GetHoldItem_Implementation(bool& IsHold, TScriptInterface<IHorrorHoldableInterface>& HoldableItem) const override;
	virtual TScriptInterface<IHorrorHoldableInterface> GetHoldable_Implementation() const override;
	virtual void GetHoldablePutLocation_Implementation(FHitResult& HitResult) const override;
	
public:
	UFUNCTION(BlueprintCallable)
	bool IsEmptyHand(const EHandType Type);

	UFUNCTION(BlueprintCallable)
	bool Hold(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable);

	UFUNCTION(BlueprintCallable)
	void Swap();

	UFUNCTION(BlueprintCallable)
	void Release(const EHandType Type);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Lerp(float Deleta);
	virtual void Lerp_Implementation(float Deleta);

	bool CheckPutable(const FHitResult& HitResult) const;

	void SetStart(const EHandType Type, const TScriptInterface<IHorrorHoldableInterface>& Holdable);

	const FHoldStruct* GetHoldStruct(const EHandType Type) const;
	FHoldStruct* GetHoldStruct(const EHandType Type);

	const FHoldStruct& GetRightStruct() const;
	const FHoldStruct& GetLeftStruct() const;

	FHoldStruct& GetRightStruct();
	FHoldStruct& GetLeftStruct();

	bool CompareHoldedObject(IHorrorHoldableInterface* LeftObject, IHorrorHoldableInterface* RightObject) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EHandType HandDominance = EHandType::RIGHT;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct RightHand = FHoldStruct(FVector(0.f, 20.f, 0.f));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHoldStruct LeftHand = FHoldStruct(FVector(0.f, -20.f, 0.f));
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartOffset = FVector(0.f, 0.f, -30.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LerpSpeed = 5.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HandLength = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETraceTypeQuery> TracePutLocationQueryType;
};

