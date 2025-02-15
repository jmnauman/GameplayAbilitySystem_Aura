// Copyright Druid Mechanics


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult, bool& bMouseDataWasStored)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
		bMouseDataWasStored = true;
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
		bMouseDataWasStored = false;
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);

	if (OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			
			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(OwnerCharacter);

			FHitResult HitResult;

			// We use a sphere trace to make this a little more "spongy" than a line trace
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				SocketLocation,
				BeamTargetLocation,
				10.f,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,  //EDrawDebugTrace::ForDuration, //Use this to visualize
				HitResult,
				true);

			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}

		ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor);
		if (CombatInterface &&
			!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> WithinRadius;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);

	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(
		GetAvatarActorFromActorInfo(),
		WithinRadius,
		ActorsToIgnore,
		850.f, // Could parameterize this based on level if we wanted to
		MouseHitActor->GetActorLocation());

	//int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);
	int32 NumAdditionalTargets = 5;

	UAuraAbilitySystemLibrary::GetClosestTargets(
		NumAdditionalTargets,
		WithinRadius,
		OutAdditionalTargets,
		MouseHitActor->GetActorLocation(),
		FName("Enemy"));

	for (AActor* Target : OutAdditionalTargets)
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target);
		if (CombatInterface &&
			!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
		}
	}
}

void UAuraBeamSpell::RemoveOnDeathNotifyFromPrimaryTarget()
{
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if (CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().RemoveDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraBeamSpell::RemoveOnDeathNotifyFromAdditionalTarget(AActor *Actor)
{
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Actor))
	{
		if (CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().RemoveDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
		}
	}
}
