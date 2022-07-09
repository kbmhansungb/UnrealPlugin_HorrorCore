// 2022 06    Bum moo, Kim    Free copyright

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorHoldableInterface.generated.h"

class AActor;
class IHorrorHandInterface;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHorrorHoldableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSYSTEM_API IHorrorHoldableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	AActor* GetHoldableActor() const;
	virtual AActor* GetHoldableActor_Implementation() const { return nullptr; }
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	bool IsHoldable(const TScriptInterface<IHorrorHandInterface>& HandInterface) const;
	virtual bool IsHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) const { return false; }
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void ResponseHoldHoldable(const TScriptInterface<IHorrorHandInterface>& HandInterface);
	virtual void ResponseHoldHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) {};

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void SetHoldableTransform(const FTransform& DesireTransform);
	virtual void SetHoldableTransform_Implementation(const FTransform& DesireTransform) {};

	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void LerpHoldableTransform(const FTransform& DesireTransform);
	virtual void LerpHoldableTransform_Implementation(const FTransform& DesireTransform) {};
	
	UFUNCTION(Category = "Horror", BlueprintCallable, BlueprintNativeEvent)
	void ResponseReleaseHoldable(const TScriptInterface<IHorrorHandInterface>& HandInterface);
	virtual void ResponseReleaseHoldable_Implementation(const TScriptInterface<IHorrorHandInterface>& HandInterface) {};
};
