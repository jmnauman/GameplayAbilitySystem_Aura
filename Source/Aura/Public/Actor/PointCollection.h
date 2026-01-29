

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointCollection.generated.h"

UCLASS()
class AURA_API APointCollection : public AActor
{
	GENERATED_BODY()
	
public:	
	APointCollection();

	UFUNCTION(BlueprintPure)
	TArray<USceneComponent*> GetGroundPoints(const FVector& GroundLocation, int32 NumPoints, float YawOverride = 0.f);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<USceneComponent*> Points;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt0;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt1;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt2;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt3;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt4;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt5;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt6;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt7;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt8;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt9;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)	
	TObjectPtr<USceneComponent> Pt10;
};
