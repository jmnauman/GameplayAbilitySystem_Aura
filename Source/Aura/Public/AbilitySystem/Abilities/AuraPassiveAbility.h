

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraPassiveAbility.generated.h"

/**
 * Passive abilities stay activated once active, until they're manually deactivated. In-game, this activation
 * corresponds to selection in the spell menu. They're passive in the sense that they don't need to be triggered
 * once they've been assigned.
 */
UCLASS()
class AURA_API UAuraPassiveAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const
		FGameplayEventData* TriggerEventData) override;

	void OnDeactivated(const FGameplayTag& AbilityTag);
};
